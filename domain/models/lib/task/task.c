#include <task.h>
#include <string.h>

static sat_status_t task_args_is_valid (const char *const name, const char *const description);
static void task_copy_args (task_t *const object, const char *const name, const char *const description);

sat_status_t task_create (task_t *const object, const char *const name, const char *const description)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "Task object is NULL");

        status = task_args_is_valid (name, description);
        sat_status_break_on_error (status);

        memset (object, 0, sizeof (task_t));

        task_copy_args (object, name, description);

    } while (false);

    return status;
}

sat_status_t task_create_with_id (task_t *const object, uint32_t id, const char *const name, const char *const description)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "Task object is NULL");

        status = task_args_is_valid (name, description);
        sat_status_break_on_error (status);

        memset (object, 0, sizeof (task_t));

        task_copy_args (object, name, description);

        object->id = id;

    } while (false);

    return status;
}

sat_status_t task_update (task_t *const object, const char *const name, const char *const description)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "Task object is NULL");

        status = task_args_is_valid (name, description);
        sat_status_break_on_error (status);

        task_copy_args (object, name, description);

    } while (false);

    return status;
}

sat_status_t task_set_done (task_t *const object, bool done)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "Task object is NULL");

        object->done = done;

    } while (false);

    return status;
}

static sat_status_t task_args_is_valid (const char *const name, const char *const description)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, name, "Task name is NULL");
        sat_status_break_if_equals (status, strlen (name), 0, "Task name is empty");

        sat_status_break_if_null (status, description, "Task description is NULL");
        sat_status_break_if_equals (status, strlen (description), 0, "Task description is empty");

    } while (false);

    return status;
}

static void task_copy_args (task_t *const object, const char *const name, const char *const description)
{
    strncpy (object->name, name, TASK_NAME_SIZE);
    strncpy (object->description, description, TASK_DESCRIPTION_SIZE);
    object->done = false;
}