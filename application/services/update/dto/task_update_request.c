#include <task_update_request.h>
#include <common.h>
#include <string.h>

sat_status_t task_update_request_new (task_update_request_t *const object, const char *const id, const char *const name, const char *const description)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        uint32_t id_value;

        sat_status_break_if_null (status, object, "task_update_request_t is null");
        sat_status_break_if_null (status, id, "ID is null");
        sat_status_break_if_null (status, name, "Name is null");
        sat_status_break_if_null (status, description, "Description is null");

        sat_status_break_if_false (status, common_is_a_number (id), "ID is not a number");

        id_value = (uint32_t) strtoul (id, NULL, 10);

        memset (object, 0, sizeof (task_update_request_t));

        object->id = id_value;
        object->name = name;
        object->description = description;

    } while (false);

    return status;
}