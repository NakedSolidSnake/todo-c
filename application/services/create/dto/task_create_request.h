#ifndef TASK_CREATE_REQUEST_H
#define TASK_CREATE_REQUEST_H

#include <sat.h>

typedef struct
{
    const char *name;
    const char *description;
} task_create_request_t;


sat_status_t task_create_request_new (task_create_request_t *const object,
                                      const char *const name,
                                      const char *const description);

#endif /* TASK_CREATE_REQUEST_H */
