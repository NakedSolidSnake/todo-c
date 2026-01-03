#include <handler_remove.h>
#include <string.h>
#include <web_send.h>
#include <web.h>
#include <web_response.h>

int handler_remove (struct mg_connection *conn, void *data)
{
    int http_status = sat_webserver_http_status_not_found;
    web_t *const web = (web_t *const) data;
    sat_status_t status;
    char id [32] = {0};

    do 
    {
        sat_status_break_if_null (status, web, "web_t is null");

        const struct mg_request_info *ri = mg_get_request_info (conn);
        sat_status_break_if_null (status, ri, "mg_request_info is null");

        sat_status_break_if_null (status, ri->query_string, "query_string is null");

        mg_get_var (ri->query_string, strlen (ri->query_string), "id", id, sizeof (id));

        todo_action_args_t args;
        todo_action_args_new_first (&args, TODO_COMMAND_REMOVE, id);

        todo_action_result_t result;
        status = todo_process (&web->todo, &args, &result);
        sat_status_break_on_error (status);

        sat_status_set (&status, true, translate_get_text_by (&web->translate, type_success_task_remove));
        http_status = sat_webserver_http_status_ok;

    } while (false);

    const char *message = web_response_create (sat_status_get_result (&status), sat_status_get_motive (&status));

    sat_log_info ("Remove Handler Response: %s", message);

    return web_send_response (conn, message, http_status);
}