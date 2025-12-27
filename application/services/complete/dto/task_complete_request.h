#ifndef TASK_COMPLETE_REQUEST_H
#define TASK_COMPLETE_REQUEST_H

#include <stdint.h>
#include <sat.h>

typedef struct
{
    uint32_t id;

} task_complete_request_t;

sat_status_t task_complete_request_new (task_complete_request_t *const object, const char *const id);

#endif /* TASK_COMPLETE_REQUEST_H */
