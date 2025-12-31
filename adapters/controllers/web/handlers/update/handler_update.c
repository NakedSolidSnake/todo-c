#include <handler_update.h>
#include <update_request.h>
#include <string.h>
#include <todo.h>
#include <web_send.h>

int handler_update (struct mg_connection *conn, void *data)
{
    todo_t *const todo = (todo_t *const) data;

    sat_status_t status;
    int http_status = sat_webserver_http_status_ok;
    char body [1280] = {0};
    char *response = "{\"message\": \"Task Updated successfully\"}";

    do
    {
        sat_status_break_if_null (status, todo, "todo_t is null");
        
        int body_length = mg_read (conn, body, sizeof (body) - 1);
        if (body_length <= 0)
        {
            response = "{\"message\": \"Failed to read request body\"}";
            http_status = sat_webserver_http_status_bad_request;
            break;
        }

        body [body_length] = '\0';

        update_request_t request;
        sat_json_t json;
        sat_json_mapper_t mapper [] = 
        {
            {.token = "id", .data = request.id, .type = sat_json_type_string, .size = sizeof (request.id)},
            {.token = "name", .data = request.name, .type = sat_json_type_string, .size = sizeof (request.name)},
            {.token = "description", .data = request.description, .type = sat_json_type_string, .size = sizeof (request.description)}
        };

        sat_json_init (&json);
        status = sat_json_deserialize (&json, body, mapper, 3);
        sat_status_break_on_error (status);

        todo_action_args_t args;

        todo_action_args_new_all (&args, TODO_COMMAND_UPDATE, request.id, request.name, request.description);

        todo_action_result_t result;
        status = todo_process (todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            http_status = sat_webserver_http_status_bad_request;
            response = "{\"message\": \"Failed to update task\"}";
            break;
        }

    } while (false);

    return web_send_response (conn, response, http_status); 
}