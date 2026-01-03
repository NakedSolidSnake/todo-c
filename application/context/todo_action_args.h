#ifndef TODO_ACTION_ARGS_H
#define TODO_ACTION_ARGS_H

#include <sat.h>
#include <task.h>

#define TODO_COMMAND_FIELD_SIZE    10
#define TODO_PARAMETERS_FIELD_SIZE  255

typedef struct 
{
    char command [TODO_COMMAND_FIELD_SIZE + 1];

    struct 
    {
        char first [TODO_PARAMETERS_FIELD_SIZE + 1];
        char second [TODO_PARAMETERS_FIELD_SIZE + 1];
        char third [TODO_PARAMETERS_FIELD_SIZE + 1];
    } parameters;
    
} todo_action_args_t;

sat_status_t todo_action_args_new (todo_action_args_t *const object, const char *const command);
sat_status_t todo_action_args_new_first (todo_action_args_t *const object, const char *const command, const char *const first);
sat_status_t todo_action_args_new_first_second (todo_action_args_t *const object, const char *const command, const char *const first, const char *const second);
sat_status_t todo_action_args_new_all (todo_action_args_t *const object, const char *const command, const char *const first, const char *const second, const char *const third);

#endif /* TODO_ACTION_ARGS_H */
