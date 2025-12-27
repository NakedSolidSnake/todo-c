#ifndef CONTROLLER_BASE_H
#define CONTROLLER_BASE_H

#include <sat.h>

typedef struct
{
    void *object;
    sat_status_t (*open) (void *const object, const void *const args);
    sat_status_t (*run) (void *const object);
    sat_status_t (*close) (void *const object);

    sat_status_t (*add) (void *const object);
    sat_status_t (*display) (void *const object);
    sat_status_t (*remove) (void *const object);
    sat_status_t (*update) (void *const object);
    sat_status_t (*complete) (void *const object);

} controller_base_t;

#endif /* CONTROLLER_BASE_H */
