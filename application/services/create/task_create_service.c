#include <task_create_service.h>

sat_status_t task_create_service_open (task_create_service_t *const object, const task_create_service_args_t *const args)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "task_create_service_t is null");
        sat_status_break_if_null (status, args, "task_create_service_args_t is null");

        object->repository = args->repository;

    } while (false);

    return status;
}

sat_status_t task_create_service_perform (task_create_service_t *const object, const task_create_request_t *const request)
{
    sat_status_t status;
    task_t task;

    do
    {
        sat_status_break_if_null (status, object, "task_create_service_t is null");
        sat_status_break_if_null (status, request, "task_create_request_t is null");

        status = object->repository->find_by_name (object->repository->object, request->name, &task);
        if (sat_status_get_result (&status) == true)
        {
            status = sat_status_failure (&status, "Task with the same name already exists");
            break;
        }

        status = task_create (&task, request->name, request->description);
        sat_status_break_on_error (status);

        status = object->repository->store (object->repository->object, &task);

    } while (false);

    return status;
}