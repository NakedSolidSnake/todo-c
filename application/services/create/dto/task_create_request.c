#include <task_create_request.h>
#include <common.h>

sat_status_t task_create_request_new (task_create_request_t *const object,
                                      const char *const name,
                                      const char *const description)
{
    sat_status_t status = sat_status_success (&status);
    do
    {
        sat_status_break_if_null (status, object, "task_create_request_t is null");
        sat_status_break_if_null (status, name, "Name is null");
        sat_status_break_if_null (status, description, "Description is null");

        object->name = name;
        object->description = description;

    } while (false);

    return status;
}