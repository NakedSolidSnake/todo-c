#include <task_complete_service.h>

sat_status_t task_complete_service_open (task_complete_service_t *const object, const task_complete_service_args_t *const args)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "task_complete_service_t is null");
        sat_status_break_if_null (status, args, "task_complete_service_args_t is null");

        object->repository = args->repository;

    } while (false);

    return status;
}

sat_status_t task_complete_service_perform (task_complete_service_t *const object, const task_complete_request_t *const request)
{
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "task_complete_service_t is null");
        sat_status_break_if_null (status, request, "task_complete_request_t is null");

        status = object->repository->complete_by_id (object->repository->object, request->id);

    } while (false);

    return status;
}