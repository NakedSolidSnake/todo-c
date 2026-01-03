#ifndef WEB_H
#define WEB_H

#include <controller_base.h>
#include <todo.h>
#include <translate.h>

typedef struct
{
    controller_base_t base;
    /* Add Web specific members here */
    sat_webserver_t server;
    translate_t translate;
    todo_t todo;
    bool running;
    // sat_set_t *routes;  /* Example member for web routes */
} web_t;

typedef struct
{
    /* Add Web specific arguments here */
    task_repository_t *repository;
} web_args_t;

sat_status_t web_init (web_t *const object);

#endif /* WEB_H */
