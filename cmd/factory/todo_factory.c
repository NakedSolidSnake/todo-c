#include <todo_factory.h>
#include <cli.h>
#include <stdlib.h>

static controller_base_t *todo_factory_create_cli (void);

controller_base_t *todo_factory_create_controller (todo_factory_type_t type)
{
    controller_base_t *controller = NULL;

    switch (type)
    {
        case todo_factory_type_cli:

            controller = todo_factory_create_cli ();

            break;

        /* Future types can be handled here */

        default:
            break;
    }

    return controller;
}

void todo_factory_destroy_controller (controller_base_t *const controller)
{
    if (controller != NULL)
    {
        free (controller);
    }
}

static controller_base_t *todo_factory_create_cli (void)
{
    cli_t *const cli = (cli_t *const) malloc (sizeof (cli_t));

    if (cli == NULL)
    {

    }

    cli_init (cli);

    return (controller_base_t *const) cli;
}