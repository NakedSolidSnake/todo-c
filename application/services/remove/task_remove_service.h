#ifndef TASK_REMOVE_SERVICE_H
#define TASK_REMOVE_SERVICE_H

#include <task_repository.h>
#include <task_remove_request.h>

typedef struct
{
    task_repository_t *repository;

} task_remove_service_t;

typedef struct
{
    task_repository_t *repository;

} task_remove_service_args_t;

sat_status_t task_remove_service_open (task_remove_service_t *const object, const task_remove_service_args_t *const args);
sat_status_t task_remove_service_perform (task_remove_service_t *const object, const task_remove_request_t *const request);

#endif /* TASK_REMOVE_SERVICE_H */
