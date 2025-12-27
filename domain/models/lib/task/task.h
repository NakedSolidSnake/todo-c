#ifndef TASK_H_
#define TASK_H_

#include <sat.h>
#include <stdint.h>

#define TASK_NAME_SIZE        100
#define TASK_DESCRIPTION_SIZE 255

typedef struct 
{
    uint32_t id;
    char name [TASK_NAME_SIZE + 1];
    char description [TASK_DESCRIPTION_SIZE + 1];
    bool done;
} task_t;

sat_status_t task_create (task_t *const object, const char *const name, const char *const description);
sat_status_t task_create_with_id (task_t *const object, uint32_t id, const char *const name, const char *const description);
sat_status_t task_update (task_t *const object, const char *const name, const char *const description);
sat_status_t task_set_done (task_t *const object, bool done);

#endif/* TASK_H_ */

