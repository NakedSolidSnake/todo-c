#include <todo.h>
#include <string.h>

typedef sat_status_t (*todo_action_handler_t) (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);

typedef struct 
{
    const char *command;
    todo_action_handler_t handler;

} todo_action_t;

static sat_status_t todo_command_is_valid (const char *const command);
static bool todo_is_equal (const void *element, const void *new_element);
static bool todo_compare_by_command (const void *element, const void *param);
static sat_status_t todo_action_add (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);
static sat_status_t todo_action_display (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);
static sat_status_t todo_action_remove (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);
static sat_status_t todo_action_update (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);
static sat_status_t todo_action_complete (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result);
sat_status_t todo_open (todo_t *const object, const todo_args_t *const args)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_t is null");
        sat_status_break_if_null (status, args, "todo_args_t is null");
        sat_status_break_if_null (status, args->repository, "task_repository_t is null");

        status = task_create_service_open (&object->services.create, &(task_create_service_args_t) { .repository = args->repository });
        sat_status_break_on_error (status);

        status = task_remove_service_open (&object->services.remove, &(task_remove_service_args_t) { .repository = args->repository });
        sat_status_break_on_error (status);

        status = task_update_service_open (&object->services.update, &(task_update_service_args_t) { .repository = args->repository });
        sat_status_break_on_error (status);

        status = task_complete_service_open (&object->services.complete, &(task_complete_service_args_t) { .repository = args->repository });
        sat_status_break_on_error (status);

        status = sat_set_create (&object->commands, &(sat_set_args_t)
                                                    {
                                                        .size = 5,
                                                        .object_size = sizeof (todo_action_t),
                                                        .is_equal = todo_is_equal,
                                                        .mode = sat_set_mode_static
                                                    });
        sat_status_break_on_error (status);

        sat_set_add (object->commands, &(todo_action_t) {.command = TODO_COMMAND_ADD,      .handler = todo_action_add});
        sat_set_add (object->commands, &(todo_action_t) {.command = TODO_COMMAND_DISPLAY,  .handler = todo_action_display});
        sat_set_add (object->commands, &(todo_action_t) {.command = TODO_COMMAND_REMOVE,   .handler = todo_action_remove});
        sat_set_add (object->commands, &(todo_action_t) {.command = TODO_COMMAND_UPDATE,   .handler = todo_action_update});
        sat_set_add (object->commands, &(todo_action_t) {.command = TODO_COMMAND_COMPLETE, .handler = todo_action_complete});

        object->repository = args->repository;

    } while (false);

    return status;
}

sat_status_t todo_process (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "action_manager_t is null");
        sat_status_break_if_null (status, args, "action_args_t is null");
        sat_status_break_if_null (status, result, "action_result_t is null");

        status = todo_command_is_valid (args->command);
        sat_status_break_on_error (status);

        todo_action_t *action = NULL;
        status = sat_set_get_object_ref_by_parameter (object->commands,
                                         args->command,
                                         todo_compare_by_command,
                                         (void **) &action);

        sat_status_break_on_error (status);

        status = action->handler (object, args, result);

    } while (false);

    return status;
}

sat_status_t todo_close (todo_t *const object)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_t is null");

        status = sat_set_destroy (object->commands);

    } while (false);

    return status;
}

static sat_status_t todo_command_is_valid (const char *const command)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, command, "Command is null");

        if (strcmp (command, TODO_COMMAND_ADD) != 0 &&
            strcmp (command, TODO_COMMAND_DISPLAY) != 0 &&
            strcmp (command, TODO_COMMAND_REMOVE) != 0 &&
            strcmp (command, TODO_COMMAND_UPDATE) != 0 &&
            strcmp (command, TODO_COMMAND_COMPLETE) != 0)
        {
            status = sat_status_failure (&status, "Invalid command");
            break;
        }

    } while (false);

    return status;
}

static bool todo_is_equal (const void *element, const void *new_element)
{
    const todo_action_t *action_1 = (const todo_action_t *)element;
    const todo_action_t *action_2 = (const todo_action_t *)new_element;

    return strcmp (action_1->command, action_2->command) == 0;
}

static sat_status_t todo_action_add (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status;

    do
    {
        /* Implementation of the 'add' action goes here */
        task_create_request_t request;
        status = task_create_request_new (&request, args->parameters.first, args->parameters.second);
        sat_status_break_on_error (status);

        status = task_create_service_perform (&object->services.create, &request);
        sat_status_break_on_error (status);

        status = todo_action_result_new (result);

    } while (false);

    return status;
}

static sat_status_t todo_action_display (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        /* Implementation of the 'display' action goes here */
        /* This might involve fetching tasks from the repository and displaying them */
        sat_array_t *tasks;
        status = object->repository->get_all (object->repository->object, &tasks);
        sat_status_break_on_error (status);

        status = todo_action_result_new_display (result, tasks);

    } while (false);

    return status;
}

static sat_status_t todo_action_remove (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status;

    do
    {
        task_remove_request_t request;
        status = task_remove_request_new (&request, args->parameters.first);
        sat_status_break_on_error (status);

        status = task_remove_service_perform (&object->services.remove, &request);
        sat_status_break_on_error (status);

        status = todo_action_result_new (result);

    } while (false);

    return status;
}

static sat_status_t todo_action_update (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status;

    do
    {
        /* Implementation of the 'update' action goes here */
        task_update_request_t request;

        status = task_update_request_new (&request, args->parameters.first, args->parameters.second, args->parameters.third);
        sat_status_break_on_error (status);

        status = task_update_service_perform (&object->services.update, &request);
        sat_status_break_on_error (status);

        status = todo_action_result_new (result);

    } while (false);

    return status;
}

static sat_status_t todo_action_complete (todo_t *const object, const todo_action_args_t *const args, todo_action_result_t *const result)
{
    sat_status_t status;

    do
    {
        /* Implementation of the 'complete' action goes here */
        task_complete_request_t request;
        status = task_complete_request_new (&request, args->parameters.first);
        sat_status_break_on_error (status);

        status = task_complete_service_perform (&object->services.complete, &request);
        sat_status_break_on_error (status);

        status = todo_action_result_new (result);

    } while (false);

    return status;
}

static bool todo_compare_by_command (const void *element, const void *param)
{
    const todo_action_t *action = (const todo_action_t *)element;
    const char *command = (const char *)param;

    return strcmp (action->command, command) == 0;
}