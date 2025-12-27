#ifndef TODO_H
#define TODO_H

#include <todo_types.h>
#include <task_create_service.h>
#include <task_remove_service.h>
#include <task_update_service.h>
#include <task_complete_service.h>

typedef struct
{
    struct
    {
        task_create_service_t create;
        task_remove_service_t remove;
        task_update_service_t update;
        task_complete_service_t complete;
    } services;

    sat_set_t *commands;

} todo_t;

typedef struct 
{
    task_repository_t *repository;

} todo_args_t;

sat_status_t todo_open (todo_t *const object, const todo_args_t *const args);
sat_status_t todo_process (todo_t *const object, const todo_action_args_t *const args);
sat_status_t todo_close (todo_t *const object);

#endif /* TODO_H */
