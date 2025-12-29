#ifndef TODO_ACTION_RESULT_H
#define TODO_ACTION_RESULT_H

#include <sat.h>

typedef enum
{
    todo_action_result_none,
    todo_action_result_display,    
} todo_action_result_type_t;

typedef struct
{
    todo_action_result_type_t type;
    union
    {
        sat_array_t *tasks;
    } data;
} todo_action_result_t;

sat_status_t todo_action_result_new (todo_action_result_t *const object);
sat_status_t todo_action_result_new_display (todo_action_result_t *const object, sat_array_t *const tasks);

#endif /* TODO_ACTION_RESULT_H */
