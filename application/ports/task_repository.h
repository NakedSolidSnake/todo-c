#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include <task.h>

typedef struct 
{
    void *object;
    sat_status_t (*store) (void *const object, const task_t *const task);
    sat_status_t (*find_by_name) (void *const object, const char *const name, task_t *const task);
    sat_status_t (*remove_by_id) (void *const object, const uint32_t id);
    sat_status_t (*complete_by_id) (void *const object, const uint32_t id);
    sat_status_t (*update) (void *const object, const task_t *const task);

} task_repository_t;

#endif /* TASK_REPOSITORY_H */
