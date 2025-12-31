#include <handler_complete.h>
#include <string.h>
#include <todo.h>
#include <web_send.h>

int handler_complete (struct mg_connection *conn, void *data)
{
    int http_status = sat_webserver_http_status_not_found;
    const char *message = "{\"message\": \"Not Found\"}";
    todo_t *const todo = (todo_t *const) data;
    sat_status_t status;
    char body [64] = {0};
    char id [32] = {0};

    do 
    {
        sat_status_break_if_null (status, todo, "todo_t is null");

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
            {.token = "id", .data = id, .type = sat_json_type_string, .size = sizeof (id)}
        };

        status = sat_json_init (&json);
        sat_status_break_on_error (status);

        status = sat_json_deserialize (&json, body, mapper, 1);
        sat_status_break_on_error (status);

        todo_action_args_t args;
        todo_action_args_new_first (&args, TODO_COMMAND_COMPLETE, id);

        todo_action_result_t result;
        status = todo_process (todo, &args, &result);
        sat_status_break_on_error (status);

        message = "{\"message\": \"Task completed successfully\"}";
        http_status = sat_webserver_http_status_ok;

    } while (false);

    return web_send_response (conn, message, http_status);
}