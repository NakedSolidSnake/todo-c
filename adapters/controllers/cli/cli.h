#ifndef CLI_H
#define CLI_H

#include <controller_base.h>
#include <todo.h>

typedef struct
{
    controller_base_t base;
    /* Add CLI specific members here */
    sat_set_t *commands;
    todo_t todo;
    bool running;
} cli_t;

typedef struct
{
    /* Add CLI specific arguments here */
    int dummy;  /* Placeholder member */
} cli_args_t;

sat_status_t cli_init (cli_t *const object);
// sat_status_t cli_close (cli_t *const object);

#endif /* CLI_H */
