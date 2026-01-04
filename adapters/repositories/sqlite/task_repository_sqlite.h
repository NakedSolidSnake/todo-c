#ifndef TASK_REPOSITORY_SQLITE_H
#define TASK_REPOSITORY_SQLITE_H

#include <task_repository.h>

typedef struct
{
    task_repository_t base;
    sat_sqlite_t handle;

} task_repository_sqlite_t;

sat_status_t task_repository_sqlite_open (task_repository_sqlite_t *const object, const char *const filename);

#endif /* TASK_REPOSITORY_SQLITE_H */
