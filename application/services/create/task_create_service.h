#ifndef TASK_CREATE_SERVICE_H
#define TASK_CREATE_SERVICE_H

#include <task_repository.h>
#include <task_create_request.h>

typedef struct
{
    task_repository_t *repository;

} task_create_service_t;

typedef struct
{
    task_repository_t *repository;

} task_create_service_args_t;

sat_status_t task_create_service_open (task_create_service_t *const object, const task_create_service_args_t *const args);
sat_status_t task_create_service_perform (task_create_service_t *const object, const task_create_request_t *const request);

#endif /* TASK_CREATE_SERVICE_H */
