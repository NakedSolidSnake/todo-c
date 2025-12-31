#include <handler_create.h>
#include <string.h>
#include <todo.h>
#include <web_send.h>
#include <create_request.h>

int handler_create (struct mg_connection *conn, void *data)
{
    todo_t *const todo = (todo_t *const) data;

    sat_status_t status;
    int http_status = sat_webserver_http_status_ok;
    char body [1280] = {0};
    char *response = "";

    do
    {
        sat_status_break_if_null (status, todo, "todo_t is null");
        
        const struct mg_request_info *ri = mg_get_request_info (conn);
        sat_status_break_if_null (status, ri, "mg_request_info is null");

        int body_length = mg_read (conn, body, sizeof (body) - 1);
        if (body_length <= 0)
        {
            http_status = sat_webserver_http_status_bad_request;
            break;
        }

        body [body_length] = '\0';

        create_request_t request;
        sat_json_t json;
        sat_json_mapper_t mapper [] = 
        {
            {.token = "name", .data = request.name, .type = sat_json_type_string, .size = sizeof (request.name)},
            {.token = "description", .data = request.description, .type = sat_json_type_string, .size = sizeof (request.description)}
        };

        sat_json_init (&json);
        status = sat_json_deserialize (&json, body, mapper, 2);
        sat_status_break_on_error (status);

        todo_action_args_t args;

        todo_action_args_new_first_second (&args, TODO_COMMAND_ADD, request.name, request.description);

        todo_action_result_t result;
        status = todo_process (todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            http_status = sat_webserver_http_status_bad_request;
            break;
        }

    } while (false);

    return web_send_response (conn, response, http_status);   
}