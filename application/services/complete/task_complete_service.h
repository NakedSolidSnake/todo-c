#ifndef TASK_COMPLETE_SERVICE_H
#define TASK_COMPLETE_SERVICE_H

#include <task_repository.h>
#include <task_complete_request.h>

typedef struct
{
    task_repository_t *repository;

} task_complete_service_t;

typedef struct
{
    task_repository_t *repository;

} task_complete_service_args_t;

sat_status_t task_complete_service_open (task_complete_service_t *const object, const task_complete_service_args_t *const args);
sat_status_t task_complete_service_perform (task_complete_service_t *const object, const task_complete_request_t *const request);

#endif /* TASK_COMPLETE_SERVICE_H */
