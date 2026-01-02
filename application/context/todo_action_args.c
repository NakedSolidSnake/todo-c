#include <todo_action_args.h>
#include <string.h>

sat_status_t todo_action_args_new (todo_action_args_t *const object, const char *const command)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_args_t is null");
        sat_status_break_if_null (status, command, "command is null");

        memset (object, 0, sizeof (todo_action_args_t));

        strncpy (object->command, command, TODO_COMMAND_FIELD_SIZE);

    } while (false);

    return status;
}

sat_status_t todo_action_args_new_first (todo_action_args_t *const object, const char *const command, const char *const first)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_args_t is null");
        sat_status_break_if_null (status, command, "command is null");
        sat_status_break_if_null (status, first, "first parameter is null");

        memset (object, 0, sizeof (todo_action_args_t));

        strncpy (object->command, command, TODO_COMMAND_FIELD_SIZE);
        strncpy (object->parameters.first, first, TODO_PARAMETERS_FIELD_SIZE);

    } while (false);

    return status;
}

sat_status_t todo_action_args_new_first_second (todo_action_args_t *const object, const char *const command, const char *const first, const char *const second)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_args_t is null");
        sat_status_break_if_null (status, command, "command is null");
        sat_status_break_if_null (status, first, "first parameter is null");
        sat_status_break_if_null (status, second, "second parameter is null");

        memset (object, 0, sizeof (todo_action_args_t));

        strncpy (object->command, command, TODO_COMMAND_FIELD_SIZE);
        strncpy (object->parameters.first, first, TODO_PARAMETERS_FIELD_SIZE);
        strncpy (object->parameters.second, second, TODO_PARAMETERS_FIELD_SIZE);

    } while (false);

    return status;
}

sat_status_t todo_action_args_new_all (todo_action_args_t *const object, const char *const command, const char *const first, const char *const second, const char *const third)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_args_t is null");
        sat_status_break_if_null (status, command, "command is null");
        sat_status_break_if_null (status, first, "first parameter is null");
        sat_status_break_if_null (status, second, "second parameter is null");
        sat_status_break_if_null (status, third, "third parameter is null");

        memset (object, 0, sizeof (todo_action_args_t));

        strncpy (object->command, command, TODO_COMMAND_FIELD_SIZE);
        strncpy (object->parameters.first, first, TODO_PARAMETERS_FIELD_SIZE);
        strncpy (object->parameters.second, second, TODO_PARAMETERS_FIELD_SIZE);
        strncpy (object->parameters.third, third, TODO_PARAMETERS_FIELD_SIZE);

    } while (false);

    return status;
}