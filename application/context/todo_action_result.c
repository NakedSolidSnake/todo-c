#include <todo_action_result.h>

sat_status_t todo_action_result_new (todo_action_result_t *const object)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_result_t is null");

        object->type = todo_action_result_none;

    } while (false);

    return status;
}

sat_status_t todo_action_result_new_display (todo_action_result_t *const object, sat_array_t *const tasks)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "todo_action_result_t is null");
        sat_status_break_if_null (status, tasks, "tasks array is null");

        object->type = todo_action_result_display;
        object->data.tasks = tasks;

    } while (false);

    return status;
}