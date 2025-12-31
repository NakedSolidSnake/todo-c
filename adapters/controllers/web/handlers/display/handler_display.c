#include <handler_display.h>
#include <string.h>
#include <web_send.h>
#include <todo.h>

int handler_display (struct mg_connection *conn, void *data)
{
    char buffer [8192] = {0};
    sat_status_t status;
    todo_t *const todo = (todo_t *const) data;
    sat_json_t array;
    char *s = "[]";

    do
    {
        todo_action_args_t args;
        todo_action_args_new (&args, TODO_COMMAND_DISPLAY);

        todo_action_result_t result;

        status = todo_process (todo, &args, &result);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = sat_json_init (&array);
        sat_status_break_on_error (status);

        status = sat_json_open (&array, &(sat_json_args_t){.buffer = buffer, .size = sizeof (buffer)});
        sat_status_break_on_error (status);

        status = sat_json_serialize_create_array (&array);
        sat_status_break_on_error (status);

        sat_iterator_t iterator;

        status = sat_iterator_open (&iterator, (sat_iterator_base_t *)result.data.tasks);
        if (sat_status_get_result (&status) == false)
        {
            sat_json_close (&array);
            sat_array_destroy (result.data.tasks);
            break;
        }

        task_t *task = sat_iterator_next (&iterator);
        while (task != NULL)
        {
            sat_json_t object;
            char dummy;
            status = sat_json_init (&object);
            sat_status_break_on_error (status);

            status = sat_json_open (&object, &(sat_json_args_t){.buffer = &dummy, .size = sizeof (dummy)});
            sat_status_break_on_error (status);

            status = sat_json_serialize_create_object (&object);
            sat_status_break_on_error (status);

            sat_json_serialize_add (&object, sat_json_type_int, "id", &task->id);
            sat_json_serialize_add (&object, sat_json_type_string, "name", task->name);
            sat_json_serialize_add (&object, sat_json_type_string, "description", task->description);
            sat_json_serialize_add (&object, sat_json_type_string, "status", task->done ? "completed" : "pending");

            sat_json_serialize_add (&array, sat_json_type_object, "", object.json);

            task = sat_iterator_next (&iterator);
        }

        sat_json_to_string (&array, &s);

        sat_array_destroy (result.data.tasks);
        
    } while (false);

    return web_send_response (conn, s, sat_webserver_http_status_ok);
}