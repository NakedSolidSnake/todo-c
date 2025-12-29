#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <sat.h>
#include <task_repository.h>

typedef struct
{
    task_repository_t *repository;
} controller_base_args_t;

typedef struct
{
    void *object;
    sat_status_t (*open) (void *const object, const controller_base_args_t *const args);
    sat_status_t (*run) (void *const object);
    sat_status_t (*close) (void *const object);

    sat_status_t (*add) (void *const object);
    sat_status_t (*display) (void *const object);
    sat_status_t (*remove) (void *const object);
    sat_status_t (*update) (void *const object);
    sat_status_t (*complete) (void *const object);

} controller_base_t;

#endif /* CONTROLLER_BASE_H */
