#ifndef TASK_UPDATE_SERVICE_H
#define TASK_UPDATE_SERVICE_H

#include <task_repository.h>
#include <task_update_request.h>

typedef struct
{
    task_repository_t *repository;

} task_update_service_t;

typedef struct
{
    task_repository_t *repository;

} task_update_service_args_t;

sat_status_t task_update_service_open (task_update_service_t *const object, const task_update_service_args_t *const args);
sat_status_t task_update_service_perform (task_update_service_t *const object, const task_update_request_t *const request);

#endif /* TASK_UPDATE_SERVICE_H */
