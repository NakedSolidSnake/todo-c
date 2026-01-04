#include <web.h>
#include <string.h>
#include <unistd.h>
#include <handler_health.h>
#include <handler_complete.h>
#include <handler_create.h>
#include <handler_display.h>
#include <handler_remove.h>
#include <handler_shutdown.h>
#include <handler_update.h>
#include <handler_schema.h>

static sat_status_t web_open (void *const object, const controller_base_args_t *const args);
static sat_status_t web_run (void *const object);
static sat_status_t web_close (void *const object);

sat_status_t web_init (web_t *const object)
{
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "web_t is null");

        memset (object, 0, sizeof (web_t));

        status = sat_webserver_init (&object->server);
        sat_status_break_on_error (status);

        object->base.object = object;
        object->base.open  = web_open;
        object->base.close = web_close;
        object->base.run   = web_run;

    } while (false);

    return status;
}

static sat_status_t web_open (void *const object, const controller_base_args_t *const args)
{
    sat_status_t status = sat_status_success (&status);
    web_t *const web = (web_t *const) object;

    do
    {
        sat_status_break_if_null (status, web, "web_t is null");
        sat_status_break_if_null (status, args, "web_args_t is null");

        translate_init (&web->translate, args->config->application.language);

        sat_webserver_args_t web_args =
        {
            .port = args->config->webserver.port,
            .folder = ".",
            .threads_amount = "1",
            .endpoint_amount = 8,
            .mode = sat_webserver_mode_static
        };

        status = sat_webserver_open (&web->server, &web_args);
        sat_status_break_on_error (status);

        status = todo_open (&web->todo, &(todo_args_t) { .repository = args->repository });
        sat_status_break_on_error (status);

        status = sat_webserver_add_endpoint (&web->server, "/health", "GET", handler_health, NULL);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/create", "POST", handler_create, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/display", "GET", handler_display, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/remove", "DELETE", handler_remove, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/update", "PUT", handler_update, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/complete", "POST", handler_complete, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/shutdown", "POST", handler_shutdown, web);
        sat_status_break_on_error (status);
        status = sat_webserver_add_endpoint (&web->server, "/schemas", "GET", handler_schema, NULL);
        sat_status_break_on_error (status);

        web->running = true;

    } while (false);
    
    return status;
}

static sat_status_t web_run (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    web_t *const web = (web_t *const) object;

    do
    {
        sat_status_break_if_null (status, web, "web_t is null");
        do
        {
            status = sat_webserver_run (&web->server);

            usleep (1);

            if (web->running == false)
            {
                sleep (1);
                sat_webserver_stop (&web->server);
                break;
            }

        } while (sat_status_get_result (&status) == true);

    } while (false);

    return status;
}

static sat_status_t web_close (void *const object)
{
    sat_status_t status = sat_status_success (&status);
    web_t *const web = (web_t *const) object;

    do
    {
        sat_status_break_if_null (status, web, "web_t is null");

        status = sat_webserver_close (&web->server);

    } while (false);

    return status;
}