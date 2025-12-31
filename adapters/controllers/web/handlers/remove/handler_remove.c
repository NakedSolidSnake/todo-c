#include <handler_remove.h>
#include <string.h>
#include <web_send.h>
#include <todo.h>

int handler_remove (struct mg_connection *conn, void *data)
{
    int http_status = sat_webserver_http_status_not_found;
    const char *message = "{\"message\": \"Not Found\"}";
    todo_t *const todo = (todo_t *const) data;
    sat_status_t status;
    char id [32] = {0};

    do 
    {
        sat_status_break_if_null (status, todo, "todo_t is null");

        const struct mg_request_info *ri = mg_get_request_info (conn);
        sat_status_break_if_null (status, ri, "mg_request_info is null");

        sat_status_break_if_null (status, ri->query_string, "query_string is null");

        mg_get_var (ri->query_string, strlen (ri->query_string), "id", id, sizeof (id));

        todo_action_args_t args;
        todo_action_args_new_first (&args, TODO_COMMAND_REMOVE, id);

        todo_action_result_t result;
        status = todo_process (todo, &args, &result);
        sat_status_break_on_error (status);

        message = "{\"message\": \"Task removed successfully\"}";
        http_status = sat_webserver_http_status_ok;

    } while (false);

    return web_send_response (conn, message, http_status);
}