#include <handler_schema.h>
#include <string.h>
#include <web_send.h>

static const char *get_endpoints_list (void)
{
    return 
    "{"
        "\"message\": \"Todo API - Available Endpoints\","
        "\"version\": \"1.0.0\","
        "\"usage\": \"Use ?filter=<endpoint> to see detailed schema (e.g., /schema?filter=create)\","
        "\"endpoints\": [\"health\", \"display\", \"create\", \"update\", \"complete\", \"delete\"]"
    "}";
}

static const char *get_health_schema (void)
{
    return
    "{"
        "\"endpoint\": \"health\","
        "\"method\": \"GET\","
        "\"path\": \"/health\","
        "\"description\": \"Health check endpoint to verify server status\","
        "\"requestBody\": \"none\","
        "\"responseBody\":"
        "{"
            "\"status\": \"string\","
            "\"message\": \"string\""
        "},"
        "\"example\": \"curl http://localhost:1234/health\""
    "}";
}

static const char *get_display_schema (void)
{
    return
    "{"
        "\"endpoint\": \"display\","
        "\"method\": \"GET\","
        "\"path\": \"/display\","
        "\"description\": \"Retrieve all tasks from the system\","
        "\"requestBody\": \"none\","
        "\"responseBody\": "
        "{"
            "\"tasks\":"
            "[{"
                "\"id\": \"integer\","
                "\"name\": \"string\","
                "\"description\": \"string\","
                "\"completed\": \"boolean\""
            "}]"
        "},"
        "\"example\": \"curl http://localhost:1234/api/tasks\""
    "}";
}

static const char *get_create_schema(void)
{
    return
    "{"
        "\"endpoint\": \"create\","
        "\"method\": \"POST\","
        "\"path\": \"/create\","
        "\"description\": \"Create a new task in the system\","
        "\"requestBody\": {"
            "\"name\": {"
                "\"type\": \"string\","
                "\"required\": true,"
                "\"description\": \"Task name\""
            "},"
            "\"description\": {"
                "\"type\": \"string\","
                "\"required\": true,"
                "\"description\": \"Task description\""
            "}"
        "},"
        "\"responseBody\": {"
            "\"id\": \"integer\","
            "\"name\": \"string\","
            "\"description\": \"string\","
            "\"completed\": \"boolean\""
        "},"
        "\"example\": \"curl -X POST http://localhost:1234/api/tasks -H 'Content-Type: application/json' -d '{\\\"name\\\":\\\"My Task\\\",\\\"description\\\":\\\"Task description\\\"}'\""
    "}";
}

static const char *get_update_schema(void)
{
    return "{"
        "\"endpoint\": \"update\","
        "\"method\": \"PUT\","
        "\"path\": \"/update\","
        "\"description\": \"Update an existing task by ID\","        
        "\"requestBody\": {"
            "\"id\": {"
                "\"type\": \"integer\","
                "\"required\": true,"
                "\"description\": \"Task ID to update\""
            "},"
            "\"name\": {"
                "\"type\": \"string\","
                "\"required\": false,"
                "\"description\": \"New task name\""
            "},"
            "\"description\": {"
                "\"type\": \"string\","
                "\"required\": false,"
                "\"description\": \"New task description\""
            "}"
        "},"
        "\"responseBody\": {"
            "\"id\": \"integer\","
            "\"name\": \"string\","
            "\"description\": \"string\","
            "\"completed\": \"boolean\""
        "},"
        "\"example\": \"curl -X PUT http://localhost:1234/api/tasks/1 -H 'Content-Type: application/json' -d '{\\\"name\\\":\\\"Updated Task\\\",\\\"description\\\":\\\"Updated description\\\"}'\""
    "}";
}

static const char *get_complete_schema(void)
{
    return "{"
        "\"endpoint\": \"complete\","
        "\"method\": \"POST\","
        "\"path\": \"/complete\","
        "\"description\": \"Mark a task as completed\","
        "\"requestBody\": {"
            "\"id\": {"
                "\"type\": \"integer\","
                "\"required\": true,"
                "\"description\": \"Task ID to mark as completed\""
            "}"
        "},"
        "\"responseBody\": {"
            "\"id\": \"integer\","
            "\"name\": \"string\","
            "\"description\": \"string\","
            "\"completed\": \"boolean\""
        "},"
        "\"example\": \"curl -X PATCH http://localhost:1234/api/tasks/1/complete\""
    "}";
}

static const char *get_delete_schema(void)
{
    return "{"
        "\"endpoint\": \"delete\","
        "\"method\": \"DELETE\","
        "\"path\": \"/delete\","
        "\"description\": \"Delete a task from the system\","
        "\"pathParameters\": {"
            "\"id\": {"
                "\"type\": \"integer\","
                "\"required\": true,"
                "\"description\": \"Task ID to delete\""
            "}"
        "},"
        "\"requestBody\": null,"
        "\"responseBody\": {"
            "\"message\": \"string\","
            "\"deleted_id\": \"integer\""
        "},"
        "\"example\": \"curl -X DELETE http://localhost:1234/api/tasks/1\""
    "}";
}

int handler_schema (struct mg_connection *conn, void *data)
{
    char filter [64] = {0};
    const char *json_response = NULL;

    do
    {
        const struct mg_request_info *ri = mg_get_request_info (conn);
        if (ri->query_string == NULL)
        {
            json_response = get_endpoints_list ();
        }
        else
        {
            mg_get_var (ri->query_string, strlen (ri->query_string), "filter", filter, sizeof (filter));
    
            // Select schema based on filter
            if (strlen (filter) == 0)
            {
                // No filter - show endpoints list
                json_response = get_endpoints_list();
            }
            else if (strcmp(filter, "health") == 0)
            {
                json_response = get_health_schema();
            }
            else if (strcmp(filter, "display") == 0)
            {
                json_response = get_display_schema();
            }
            else if (strcmp(filter, "create") == 0)
            {
                json_response = get_create_schema();
            }
            else if (strcmp(filter, "update") == 0)
            {
                json_response = get_update_schema();
            }
            else if (strcmp(filter, "complete") == 0)
            {
                json_response = get_complete_schema();
            }
            else if (strcmp(filter, "delete") == 0)
            {
                json_response = get_delete_schema();
            }
            else
            {
                // Invalid filter - show endpoints list as fallback
                json_response = get_endpoints_list();
            }
        }
    } while (false);

    return web_send_response (conn, json_response, sat_webserver_http_status_ok);
}   