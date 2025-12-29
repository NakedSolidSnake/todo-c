#ifndef TODO_FACTORY_H
#define TODO_FACTORY_H

#include <controller_base.h>

typedef enum
{
    todo_factory_type_cli,
    /* Future types can be added here */
} todo_factory_type_t;

controller_base_t *todo_factory_create_controller (todo_factory_type_t type);
void todo_factory_destroy_controller (controller_base_t *const controller);

#endif /* TODO_FACTORY_H */
