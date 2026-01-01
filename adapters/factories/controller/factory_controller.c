#include <factory_controller.h>
#include <cli.h>
#include <web.h>
#include <stdlib.h>

typedef controller_base_t *(*factory_controller_create_t) (void);

typedef struct
{    
    const char *const type;
    factory_controller_create_t create;
} factory_controller_pair_t;

static controller_base_t *factory_controller_create_cli (void);
static controller_base_t *factory_controller_create_web (void);

static const factory_controller_pair_t factory_controller_pairs [] =
{
    { .type = "cli", .create = factory_controller_create_cli },
    { .type = "web", .create = factory_controller_create_web }
};

controller_base_t *factory_controller_create (const char *const type)
{
    controller_base_t *controller = NULL;

    for (size_t i = 0; i < sizeof (factory_controller_pairs) / sizeof (factory_controller_pair_t); i++)
    {
        if (strcmp (factory_controller_pairs [i].type, type) == 0)
        {
            controller = factory_controller_pairs [i].create ();
            break;
        }
    }

    return controller;
}

void factory_controller_destroy (controller_base_t *const controller)
{
    if (controller != NULL)
    {
        free (controller);
    }
}

static controller_base_t *factory_controller_create_cli (void)
{
    cli_t *const cli = (cli_t *const) malloc (sizeof (cli_t));

    if (cli == NULL)
    {

    }

    cli_init (cli);

    return (controller_base_t *const) cli;
}

static controller_base_t *factory_controller_create_web (void)
{
    web_t *const web = (web_t *const) malloc (sizeof (web_t));

    if (web == NULL)
    {

    }

    web_init (web);

    return (controller_base_t *const) web;
}