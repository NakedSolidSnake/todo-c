#ifndef TASK_REMOVE_REQUEST_H
#define TASK_REMOVE_REQUEST_H

#include <stdint.h>
#include <sat.h>

typedef struct
{
    uint32_t id;

} task_remove_request_t;

sat_status_t task_remove_request_new (task_remove_request_t *const object, const char *const id);

#endif /* TASK_REMOVE_REQUEST_H */
