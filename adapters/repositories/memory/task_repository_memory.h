#ifndef TASK_REPOSITORY_MEMORY_H
#define TASK_REPOSITORY_MEMORY_H

#include <task_repository.h>

typedef struct
{
    task_repository_t base;
    sat_set_t *storage;

} task_repository_memory_t;

sat_status_t task_repository_memory_open (task_repository_memory_t *const object);

#endif /* TASK_REPOSITORY_MEMORY_H */
