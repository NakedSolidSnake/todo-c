#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <task_repository.h>
#include <config.h>

typedef struct
{
    task_repository_t *repository;
    config_t *config;
} controller_base_args_t;

typedef struct
{
    void *object;
    sat_status_t (*open) (void *const object, const controller_base_args_t *const args);
    sat_status_t (*run) (void *const object);
    sat_status_t (*close) (void *const object);

} controller_base_t;

#endif /* CONTROLLER_BASE_H */
