#ifndef TODO_TYPES_H
#define TODO_TYPES_H

#define TODO_COMMAND_ADD         "add"      /* <command> <task name> <task description> */
#define TODO_COMMAND_DISPLAY     "display"  /* <command> */
#define TODO_COMMAND_REMOVE      "remove"   /* <command> <task id> */
#define TODO_COMMAND_UPDATE      "update"   /* <command> <task name> <task description> <task id> */
#define TODO_COMMAND_COMPLETE    "complete" /* <command> <task id> */

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
