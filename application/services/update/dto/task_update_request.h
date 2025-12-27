#ifndef TASK_UPDATE_REQUEST_H
#define TASK_UPDATE_REQUEST_H

#include <stdint.h>
#include <sat.h>

typedef struct
{
    uint32_t id;
    const char *name;
    const char *description;

} task_update_request_t;

sat_status_t task_update_request_new (task_update_request_t *const object, const char *const id, const char *const name, const char *const description);

#endif /* TASK_UPDATE_REQUEST_H */
