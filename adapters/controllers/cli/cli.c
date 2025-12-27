#include <cli.h>
#include <string.h>

typedef sat_status_t (*cli_command_handler_t) (void *const object);

typedef struct 
{
    const char *name;
    cli_command_handler_t handler;

} cli_command_t;

static sat_status_t cli_open (void *const object, const void *const args);
static sat_status_t cli_run (void *const object);
static sat_status_t cli_close (void *const object);
static sat_status_t cli_add (void *const object);
static sat_status_t cli_display (void *const object);
static sat_status_t cli_remove (void *const object);
static sat_status_t cli_update (void *const object);
static sat_status_t cli_complete (void *const object);

static todo_action_args_t cli_get_action_args (void);
static bool cli_wanna_proceed (const char *const text);
static bool cli_get_id (uint32_t *const id, const char *const text);

sat_status_t cli_init (cli_t *const object)
{
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "cli_t is null");

        memset (object, 0, sizeof (cli_t));

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

    } while (false);

    return status;
}

static sat_status_t cli_run (void *const object)
{
    sat_status_t status;
    cli_t *const cli = (cli_t *const) object;

    do
    {
        while (cli->running == true)
        {
            prompt_display_style (menu_logo (), style_fancy);
            prompt_display_style (menu_show (&object->translate), style_default);

            prompt_show (object);

            prompt_read_command (object);

            sat_set_get_object_ref_by_parameter (object->commands,
                                             object->buffer,
                                             cli_compare_by_command,
                                             (void **) &command);

            if (prompt_command_process (object) == false)
            {
                prompt_display_style (object,
                                    translate_get_text_by (&object->translate, type_error_command),
                                    style_error);
            }
        }
    } while (false);

    return status;
}

static sat_status_t cli_close (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {

    } while (false);

    return status;
}

static sat_status_t cli_add (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        todo_action_args_t args = cli_get_action_args (object);

        if (prompt_wanna_proceed (translate_get_text_by (&object->translate, type_question_task_add)) == true)
        {
            strncpy (args.command, COMMAND_ADD, strlen (COMMAND_ADD) + 1);

            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                    translate_get_text_by (&object->translate, type_success_task_add),
                                    style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                    translate_get_text_by (&object->translate, type_error_task_add),
                                    style_error);
            }
        }
    } while (false);

    return status;
}

static sat_status_t cli_display (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
    //     action_args_t args;

    // memset (&args, 0, sizeof (action_args_t));

    // strncpy (args.command, COMMAND_DISPLAY, strlen (COMMAND_DISPLAY) + 1);

    // action_manager_process (&object->manager, &args, &object->display);
    } while (false);

    return status;
}

static sat_status_t cli_remove (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        if (prompt_asks_for_id (translate_get_text_by (&object->translate, type_id_remove)) == true)
        {
            action_args_t args;

            memset (&args, 0, sizeof (action_args_t));

            strncpy (args.command, COMMAND_REMOVE, strlen (COMMAND_REMOVE) + 1);
            strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

            if (prompt_wanna_proceed (object,
                                    translate_get_text_by (&object->translate, type_question_task_remove)) == true)
            {
                if (action_manager_process (&object->manager, &args, &object->display) == true)
                {
                    prompt_display_style (object,
                                        translate_get_text_by (&object->translate, type_success_task_remove),
                                        style_success);

                    object->modified = true;
                }

                else
                {
                    prompt_display_style (object,
                                        translate_get_text_by (&object->translate, type_error_task_remove),
                                        style_error);
                }
            }
        }
    } while (false);

    return status;
}

static sat_status_t cli_update (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        if (prompt_asks_for_id (object,
                            translate_get_text_by (&object->translate, type_id_update)) == true)
    {

        char buffer [DEFINITIONS_FIELD_SIZE + 1] = {0};

        strncpy (buffer, object->buffer, strlen (object->buffer));

        action_args_t args = prompt_fill_action_args (object);

        if (prompt_wanna_proceed (object,
                                  translate_get_text_by (&object->translate, type_question_task_update)) == true)
        {
            strncpy (args.command, COMMAND_UPDATE, strlen (COMMAND_UPDATE) + 1);
            strncpy (args.parameters.third, buffer, strlen (buffer));

            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_success_task_update),
                                      style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_error_task_update),
                                      style_error);
            }
        }
    }
    } while (false);

    return status;
}

static sat_status_t cli_complete (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    cli_t *const cli = (cli_t *const) object;

    do
    {
        if (prompt_asks_for_id (object,
                            translate_get_text_by (&object->translate, type_id_complete)) == true)
    {
        action_args_t args;

        memset (&args, 0, sizeof (action_args_t));

        strncpy (args.command, COMMAND_COMPLETE, strlen (COMMAND_COMPLETE) + 1);
        strncpy (args.parameters.first, object->buffer, strlen (object->buffer));

        if (prompt_wanna_proceed (object,
                                  translate_get_text_by (&object->translate, type_question_task_complete)) == true)
        {
            if (action_manager_process (&object->manager, &args, &object->display) == true)
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_success_task_complete),
                                      style_success);

                object->modified = true;
            }

            else
            {
                prompt_display_style (object,
                                      translate_get_text_by (&object->translate, type_error_task_complete),
                                      style_error);
            }
        }
    }
    } while (false);

    return status;
}

static todo_action_args_t cli_get_action_args (void)
{
    action_args_t args;

    memset (&args, 0, sizeof (action_args_t));

    prompt_display_style (object,
                          translate_get_text_by (&object->translate, type_task_name),
                          style_default);

    object->reader.read (args.parameters.first, DEFINITIONS_FIELD_SIZE);

    prompt_display_style (object,
                          translate_get_text_by (&object->translate, type_task_description),
                          style_default);

    object->reader.read (args.parameters.second, DEFINITIONS_FIELD_SIZE);

    return args;
}

static bool cli_wanna_proceed (const char *const text)
{
    bool status = false;

    while (true)
    {
        prompt_display_style (object, text, style_default);

        char buffer [11] = {0};
        object->reader.read (buffer, 10);

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_yes),
                     strlen (translate_get_text_by (&object->translate, type_input_yes))) == 0)
        {
            status = true;
            break;
        }

        if (strncmp (buffer,
                     translate_get_text_by (&object->translate, type_input_no),
                     strlen (translate_get_text_by (&object->translate, type_input_no))) == 0)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_canceled),
                                  style_error);
            break;
        }

        else
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_option),
                                  style_error);
        }
    }

    return status;
}

static bool cli_get_id (uint32_t *const id, const char *const text)
{
    bool status = false;

    while (true)
    {
        prompt_display_style (object, text, style_default);

        object->reader.read (object->buffer, 10);

        if (common_is_a_number (object->buffer) == true)
        {
            status = true;
            break;
        }

        if (strncmp (object->buffer,
                     translate_get_text_by (&object->translate, type_input_exit),
                     strlen (translate_get_text_by (&object->translate, type_input_exit))) == 0)
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_canceled),
                                  style_error);
            break;
        }

        else
        {
            prompt_display_style (object,
                                  translate_get_text_by (&object->translate, type_error_task_id),
                                  style_error);
        }
    }

    return status;
}

bool cli_is_command_equal (const void *command, const void *command_new)
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