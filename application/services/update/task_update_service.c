#include <task_update_service.h>

sat_status_t task_update_service_open (task_update_service_t *const object, const task_update_service_args_t *const args)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "task_update_service_t is null");
        sat_status_break_if_null (status, args, "task_update_service_args_t is null");

        object->repository = args->repository;

    } while (false);

    return status;
}

sat_status_t task_update_service_perform (task_update_service_t *const object, const task_update_request_t *const request)
{
    sat_status_t status;
    task_t task;

    do
    {
        sat_status_break_if_null (status, object, "task_update_service_t is null");
        sat_status_break_if_null (status, request, "task_update_request_t is null");

        status = object->repository->find_by_name (object->repository->object, request->name, &task);
        if (sat_status_get_result (&status) == true && task.id != request->id)
        {
            status = sat_status_failure (&status, "Another task with the same name already exists");
            break;
        }

        status = object->repository->find_by_name (object->repository->object, request->name, &task);
        sat_status_break_on_error (status);

        status = task_create_with_id (&task, request->id, request->name, request->description);
        sat_status_break_on_error (status);

        status = object->repository->update (object->repository->object, &task);

    } while (false);

    return status;
}