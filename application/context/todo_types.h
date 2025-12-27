#ifndef TODO_TYPES_H
#define TODO_TYPES_H

#define TODO_COMMAND_FIELD_SIZE    10
#define TODO_PARAMTERS_FIELD_SIZE  255

typedef struct 
{
    char command [TODO_COMMAND_FIELD_SIZE + 1];

    struct 
    {
        char first [TODO_PARAMTERS_FIELD_SIZE + 1];
        char second [TODO_PARAMTERS_FIELD_SIZE + 1];
        char third [TODO_PARAMTERS_FIELD_SIZE + 1];
    } parameters;
    
} todo_action_args_t;



#endif /* TODO_TYPES_H */
