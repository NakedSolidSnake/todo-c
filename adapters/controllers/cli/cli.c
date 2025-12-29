#include <cli.h>
#include <prompt.h>
#include <menu.h>
#include <string.h>

typedef sat_status_t (*cli_command_handler_t) (void *const object);

typedef struct 
{
    const char *name;
    cli_command_handler_t handler;

} cli_command_t;

typedef struct
{
    char name [TODO_COMMAND_FIELD_SIZE + 1];
    char description [TODO_PARAMETERS_FIELD_SIZE + 1];

} cli_parameters_t;

static sat_status_t cli_open (void *const object, const void *const args);
static sat_status_t cli_run (void *const object);
static sat_status_t cli_close (void *const object);
static sat_status_t cli_add (void *const object);
static sat_status_t cli_display (void *const object);
static sat_status_t cli_remove (void *const object);
static sat_status_t cli_update (void *const object);
static sat_status_t cli_complete (void *const object);

static bool cli_is_command_equal (const void *command, const void *command_new);
static bool cli_compare_by_command (const void *element, const void *param);

static cli_parameters_t cli_get_parameters (const cli_t *const object);
static bool cli_wanna_proceed (const cli_t *const object, const char *const text);
static bool cli_get_id (const cli_t *const object, char id [32], const char *const text);

sat_status_t cli_init (cli_t *const object)
{
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "cli_t is null");

        memset (object, 0, sizeof (cli_t));

        translate_init (&object->translate, NULL);

        status = sat_set_create (&object->commands, &(sat_set_args_t)
                                            {
                                                .size = 5,
                                                .object_size = sizeof (cli_command_t),
                                                .is_equal = cli_is_command_equal,
                                                .mode = sat_set_mode_static
                                            });
        sat_status_break_on_error (status);

        sat_set_add (object->commands, &(cli_command_t) {.name = TODO_COMMAND_ADD,      .handler = cli_add});
        sat_set_add (object->commands, &(cli_command_t) {.name = TODO_COMMAND_DISPLAY,  .handler = cli_display});
        sat_set_add (object->commands, &(cli_command_t) {.name = TODO_COMMAND_REMOVE,   .handler = cli_remove});
        sat_set_add (object->commands, &(cli_command_t) {.name = TODO_COMMAND_UPDATE,   .handler = cli_update});
        sat_set_add (object->commands, &(cli_command_t) {.name = TODO_COMMAND_COMPLETE, .handler = cli_complete});

        object->base.object   = object;
        object->base.open     = cli_open;
        object->base.close    = cli_close;
        object->base.run      = cli_run;
        object->base.add      = cli_add;
        object->base.display  = cli_display;
        object->base.remove   = cli_remove;
        object->base.update   = cli_update;
        object->base.complete = cli_complete;
        
    } while (false);

    return status;
}

static sat_status_t cli_open (void *const object, const void *const args)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;
    const cli_args_t *const cli_args = (const cli_args_t *const) args;

    do
    {
        sat_status_break_if_null (status, cli_args, "cli_args_t is null");

        status = todo_open (&cli->todo, &(todo_args_t) { .repository = cli_args->repository });
        sat_status_break_on_error (status);

        cli->running = true;
    } while (false);

    return status;
}

static sat_status_t cli_run (void *const object)
{
    sat_status_t status;
    cli_t *const cli = (cli_t *const) object;
    char input_command [256];
    cli_command_t *command;

    do
    {
        while (cli->running == true)
        {
            prompt_display_style (menu_logo (), style_fancy);
            prompt_display_style (menu_show (&cli->translate), style_default);

            prompt_show ();

            prompt_read_command (input_command, sizeof (input_command));

            status = sat_set_get_object_ref_by_parameter (cli->commands,
                                                        input_command,
                                                        cli_compare_by_command,
                                                        (void **) &command);

            if (sat_status_get_result (&status) == false)
            {
                prompt_display_style (translate_get_text_by (&cli->translate, type_error_command), style_error);
                continue;
            }

            command->handler (object);
        }
    } while (false);

    return status;
}

static sat_status_t cli_close (void *const object)
{
    sat_status_t status;
    cli_t *const cli = (cli_t *const) object;

    do
    {
        sat_status_break_if_null (status, cli, "cli_t is null");

        status = sat_set_destroy (cli->commands);
        
    } while (false);

    return status;
}

static sat_status_t cli_add (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        cli_parameters_t parameters = cli_get_parameters (object);
        
        if (cli_wanna_proceed (cli, translate_get_text_by (&cli->translate, type_question_task_add)) == false)
        {
            break;
        }

        todo_action_args_t args;

        todo_action_args_new_first_second (&args, TODO_COMMAND_ADD, parameters.name, parameters.description);

        todo_action_result_t result;

        status = todo_process (&cli->todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            prompt_display_style (translate_get_text_by (&cli->translate, type_error_task_add), style_error);
            break;
        }

        prompt_display_style (translate_get_text_by (&cli->translate, type_success_task_add), style_success);

    } while (false);

    return status;
}

static sat_status_t cli_display (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        todo_action_args_t args;
        todo_action_args_new (&args, TODO_COMMAND_DISPLAY);

        todo_action_result_t result;

        status = todo_process (&cli->todo, &args, &result);
        sat_status_break_on_error (status);

        /* Handle the display result here, e.g., print the tasks */
        sat_iterator_t iterator;

        status = sat_iterator_open (&iterator, (sat_iterator_base_t *)result.data.tasks);
        if (sat_status_get_result (&status) == false)
        {
            sat_array_destroy (result.data.tasks);
            break;
        }

        task_t *task = sat_iterator_next (&iterator);
        while (task != NULL)
        {
            printf ("ID: %d, Name: %s, Description: %s, Done: [%c]\n", task->id, task->name, task->description, task->done ? 'X' : ' ');
            task = sat_iterator_next (&iterator);
        }

        sat_array_destroy (result.data.tasks);
        
    } while (false);

    return status;
}

static sat_status_t cli_remove (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;
    char id [32];

    do
    {
        if (cli_get_id (cli, id, translate_get_text_by (&cli->translate, type_id_remove)) == false)
        {
            break;
        }

        todo_action_args_t args;

        todo_action_args_new_first (&args, TODO_COMMAND_REMOVE, id);

        todo_action_result_t result;

        status = todo_process (&cli->todo, &args, &result);

        if (sat_status_get_result (&status) == false)
        {
            prompt_display_style (translate_get_text_by (&cli->translate, type_error_task_remove), style_error);
            break;
        }

        prompt_display_style (translate_get_text_by (&cli->translate, type_success_task_remove), style_success);

    } while (false);

    return status;
}

static sat_status_t cli_update (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;
    char id [32];

    do
    {
        if (cli_get_id (cli, id, translate_get_text_by (&cli->translate, type_id_update)) == false)
        {
            break;
        }

        cli_parameters_t parameters = cli_get_parameters (cli);

        if (cli_wanna_proceed (cli, translate_get_text_by (&cli->translate, type_question_task_update)) == false)
        {
            break;
        }

        todo_action_args_t args;

        todo_action_args_new_all (&args, TODO_COMMAND_UPDATE, id, parameters.name, parameters.description);

        todo_action_result_t result;

        status = todo_process (&cli->todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            prompt_display_style (translate_get_text_by (&cli->translate, type_error_task_update), style_error);
            break;
        }

        prompt_display_style (translate_get_text_by (&cli->translate, type_success_task_update), style_success);

    } while (false);

    return status;
}

static sat_status_t cli_complete (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;
    char id [32];

    do
    {
        if (cli_get_id (cli, id, translate_get_text_by (&cli->translate, type_id_complete)) == false)
        {
            break;
        }

        if (cli_wanna_proceed (cli, translate_get_text_by (&cli->translate, type_question_task_complete)) == false)
        {
            break;
        }

        todo_action_args_t args;

        todo_action_args_new_first (&args, TODO_COMMAND_COMPLETE, id);

        todo_action_result_t result;

        status = todo_process (&cli->todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            prompt_display_style (translate_get_text_by (&cli->translate, type_error_task_complete), style_error);
            break;
        }

        prompt_display_style (translate_get_text_by (&cli->translate, type_success_task_complete), style_success);

    } while (false);

    return status;
}

static cli_parameters_t cli_get_parameters (const cli_t *const object)
{
    cli_parameters_t args;

    memset (&args, 0, sizeof (cli_parameters_t));
    prompt_display_style (translate_get_text_by (&object->translate, type_task_name), style_default);

    prompt_read (args.name, TODO_PARAMETERS_FIELD_SIZE);

    prompt_display_style (translate_get_text_by (&object->translate, type_task_description), style_default);

    prompt_read (args.description, TODO_PARAMETERS_FIELD_SIZE);
    return args;
}

static bool cli_wanna_proceed (const cli_t *const object, const char *const text)
{
    bool status = false;
    char buffer [11] = {0};

    while (true)
    {
        prompt_display_style (text, style_default);

        prompt_read (buffer, 10);

        if (strncmp (buffer, translate_get_text_by (&object->translate, type_input_yes),
                     strlen (translate_get_text_by (&object->translate, type_input_yes))) == 0)
        {
            status = true;
            break;
        }

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_no),
                     strlen (translate_get_text_by (&object->translate, type_input_no))) == 0)
        {
            prompt_display_style (
                                  translate_get_text_by (&object->translate, type_error_canceled),
                                  style_error);
            break;
        }

        else
        {
            prompt_display_style (
                                  translate_get_text_by (&object->translate, type_error_option),
                                  style_error);
        }
    }

    return status;
}

static bool cli_get_id (const cli_t *const object, char id [32], const char *const text)
{
    bool status = false;
    char buffer [11];

    while (true)
    {
        prompt_display_style (text, style_default);

        prompt_read (buffer, 10);

        if (common_is_a_number (buffer) == true)
        {
            memset (id, 0, 32);

            strncpy (id, buffer, strlen (buffer) - 1);

            status = true;
            break;
        }

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_exit),
                     strlen (translate_get_text_by (&object->translate, type_input_exit))) == 0)
        {
            prompt_display_style (translate_get_text_by (&object->translate, type_error_canceled), style_error);
            break;
        }

        else
        {
            prompt_display_style (
                                  translate_get_text_by (&object->translate, type_error_task_id),
                                  style_error);
        }
    }

    return status;
}

static bool cli_is_command_equal (const void *command, const void *command_new)
{
    const cli_command_t *p1 = (const cli_command_t *)command;
    const cli_command_t *p2 = (const cli_command_t *)command_new;

    return strcmp (p1->name, p2->name) == 0;
}


static bool cli_compare_by_command (const void *element, const void *param)
{
    const cli_command_t *command = (const cli_command_t *)element;
    const char *command_name = (const char *)param;
    
    return strcmp (command->name, command_name) == 0;
}