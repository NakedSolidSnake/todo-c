#include <action_manager.h>
#include <action.h>
#include <command.h>
#include <string.h>
#include <stdio.h>
#include <common.h>

#define ACTION_MANAGER_COMMAND_AMOUNT   10

static void action_manager_create_commands (action_manager_t *object);
static void action_manager_load_tasks (action_manager_t *object);

static bool action_handler_add (void *object, action_args_t *args);
static bool action_handler_display (void *object, action_args_t *args, display_base_t *display);
static bool action_handler_remove (void *object, action_args_t *args, display_base_t *display);
static bool action_handler_update (void *object, action_args_t *args);
static bool action_handler_complete (void *object, action_args_t *args);
static bool action_handler_save (void *object);

static bool action_manager_command_is_valid (action_args_t *args);


bool action_manager_open (action_manager_t *object, action_manager_args_t *args)
{
    bool status = false;

    if (object != NULL && args != NULL)
    {
        sat_status_t __status = sat_array_create (&object->actions, &(sat_array_args_t)
                                                  {   
                                                      .size = ACTION_MANAGER_COMMAND_AMOUNT,
                                                      .object_size = sizeof (action_t),
                                                      .mode = sat_array_mode_static
                                                  });

        if (sat_status_get_result (&__status) == true)
        {
            action_manager_create_commands (object);

            task_manager_open (&object->manager);

            action_manager_load_tasks (object);

            status = true;
        }
    }

    return status;
}

bool action_manager_process (action_manager_t *object, action_args_t *args, display_base_t *display)
{
    bool status = false;

    if (object != NULL && args != NULL && action_manager_command_is_valid (args) == true)
    {
        uint32_t size = 0;
        action_t action;

        sat_array_get_size (object->actions, &size);

        for (uint32_t i = 0; i < size; i ++)
        {
            sat_array_get_object_by (object->actions, i, &action);

            if (strcmp (action.command, args->command) == 0)
            {
                status = action.handler (object, args, display);
                break;
            }
        }
    }

    return status;
}


static void action_manager_create_commands (action_manager_t *object)
{
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_ADD,      .handler = action_handler_add});
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_DISPLAY,  .handler = action_handler_display});
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_REMOVE,   .handler = action_handler_remove});
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_UPDATE,   .handler = action_handler_update});
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_COMPLETE, .handler = action_handler_complete});
    sat_array_add (object->actions, &(action_t) {.command = COMMAND_SAVE,     .handler = action_handler_save});
}

static void action_manager_load_tasks (action_manager_t *object)
{
    sat_file_t file;

    char line [1024];
    task_t task;

    // <id>,<name>,<description>,<done>
    sat_file_open (&file, DEFINITION_DATABASE, sat_file_mode_read);

    while (sat_file_readline (&file, line, sizeof (line)) == true)
    {
        bool done;
        char name [DEFINITIONS_FIELD_SIZE + 1] = {0};
        char description [DEFINITIONS_FIELD_SIZE + 1] = {0};

        char *token = strtok (line, ",");
        token = strtok (NULL, ",");
        done = token [0] == '1';

        token = strtok (NULL, ",");
        strncpy (name, token, DEFINITIONS_FIELD_SIZE);

        token = strtok (NULL, ",\n");
        strncpy (description, token, DEFINITIONS_FIELD_SIZE);

        task_create (&task, name, description);
        task_set_done (&task, done);

        task_manager_add (&object->manager, &task);
    }

    sat_file_close (&file);
}   

static bool action_handler_add (void *object, action_args_t *args)
{
    bool status = true;
    action_manager_t *am = (action_manager_t *) object;
    task_t task;

    if (task_create (&task, args->parameters.first, args->parameters.second) == true)
    {
        status = task_manager_add (&am->manager, &task);
    }

    return status;
}

static bool action_handler_display (void *object, action_args_t *args, display_base_t *display)
{
    (void) args;
    action_manager_t *am = (action_manager_t *) object;
    task_t task;

    for (uint32_t i = 0; i < task_manager_get_tasks_amount (&am->manager); i ++)
    {
        if (task_manager_get_by (&am->manager, i, &task) == true)
        {
            char buffer [300] = {0};
            snprintf (buffer, 299, DEFINITION_DISPLAY_FORMAT,
                                   task.id,
                                   task.done == true ? 'X' : ' ',
                                   task.name,
                                   task.description);

            display->show (buffer);
        }
    }

    display->show ("\n\n");

    return true;
}

static bool action_handler_remove (void *object, action_args_t *args, display_base_t *display)
{
    bool status = false;

    action_manager_t *am = (action_manager_t *) object;
    task_t task;
    uint32_t index;

    if (common_is_a_number (args->parameters.first) == true)
    {
        uint32_t id = atoi (args->parameters.first);

        if (task_manager_find_by (&am->manager, id, &task, &index) == true)
        {
            status = task_manager_remove_by (&am->manager, index);
        }
    }

    return status;
}

static bool action_handler_update (void *object, action_args_t *args)
{
    bool status = false;

    action_manager_t *am = (action_manager_t *) object;
    task_t task;
    uint32_t index;

    if (common_is_a_number (args->parameters.third) == true)
    {
        uint32_t id = atoi (args->parameters.third);

        if (task_manager_find_by (&am->manager, id, &task, &index) == true &&
            task_update (&task, args->parameters.first, args->parameters.second) == true)
        {
            status = task_manager_update_by (&am->manager, index, &task);
        }
    }

    return status;
}

static bool action_handler_complete (void *object, action_args_t *args)
{
    bool status = false;

    action_manager_t *am = (action_manager_t *) object;
    task_t task;
    uint32_t index;

    if (common_is_a_number (args->parameters.first) == true)
    {
        uint32_t id = atoi (args->parameters.first);

        if (task_manager_find_by (&am->manager, id, &task, &index) == true &&
            task_set_done (&task, true) == true)
        {
            status = task_manager_update_by (&am->manager, index, &task);
        }
    }

    return status;
}

static bool action_handler_save (void *object)
{
    sat_file_t file;
    action_manager_t *am = (action_manager_t *) object;
    task_t task;

    uint32_t amount = task_manager_get_tasks_amount (&am->manager);
    sat_file_open (&file, DEFINITION_DATABASE, sat_file_mode_write);

    for (uint32_t i = 0; i < amount; i ++)
    {
        if (task_manager_get_by (&am->manager, i, &task) == true)
        {
            char buffer [300] = {0};
            snprintf (buffer, 299, DEFINITION_STORE_FORMAT,
                                   task.id,
                                   task.done == true ? 1 : 0,
                                   task.name,
                                   task.description);

            sat_file_write (&file, buffer, strlen (buffer));
        }
    }

    sat_file_close (&file);

    return true;
}

static bool action_manager_command_is_valid (action_args_t *args)
{
    bool status = false;

    if (args->command != NULL &&
        strlen (args->command) > 0)
    {
        status = true;
    }

    return status;
}