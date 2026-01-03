#include <handler_shutdown.h>
#include <string.h>
#include <web_send.h>
#include <web.h>
#include <web_response.h>

int handler_shutdown (struct mg_connection *conn, void *data)
{
    web_t *const web = (web_t *const) data;
    int http_status = sat_webserver_http_status_internal_server_error;
    sat_status_t status;
    char body [64] = {0};
    char command [32] = {0};

    do 
    {
        sat_status_break_if_null (status, web, "web_t is null");

        int body_length = mg_read (conn, body, sizeof (body) - 1);

        if (body_length <= 0)
        {
            status = sat_status_failure (&status, "Failed to read request body");
            break;
        }

        body [body_length] = '\0';

        sat_json_t json;
        sat_json_mapper_t mapper [] = 
        {
            {.token = "command", .data = command, .type = sat_json_type_string, .size = sizeof (command)}
        };

        status = sat_json_init (&json);
        sat_status_break_on_error (status);

        status = sat_json_deserialize (&json, body, mapper, 1);
        sat_status_break_on_error (status);

        if (strcmp (command, "yes") == 0)
        {
            web->running = false;
            sat_status_set (&status, true, "Server is shutting down");
            http_status = sat_webserver_http_status_ok;
        }
        else
        {
            sat_status_failure (&status, "Invalid command");
            http_status = sat_webserver_http_status_bad_request;
        }


    } while (false);

    const char *message = web_response_create (sat_status_get_result (&status), sat_status_get_motive (&status));

    return web_send_response (conn, message, http_status);
}