#include <task_complete_request.h>
#include <common.h>
#include <stdio.h>

sat_status_t task_complete_request_new (task_complete_request_t *const object, const char *const id)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        uint32_t id_value;

        sat_status_break_if_null (status, object, "task_complete_request_t is null");
        sat_status_break_if_null (status, id, "ID is null");

        sat_status_break_if_false (status, common_is_a_number (id), "ID is not a number");

        id_value = (uint32_t) strtoul (id, NULL, 10);

        object->id = id_value;

    } while (false);

    return status;
}