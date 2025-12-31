#include <handler_schema.h>
#include <string.h>
#include <web_send.h>

int handler_schema (struct mg_connection *conn, void *data)
{
    char *json_response = "{"
                            "\"message\": \"Hello from Todo Webserver!\","
                            "\"endpoint\": \"/schema\""                            
                            "}";

    
    return web_send_response (conn, json_response, sat_webserver_http_status_ok);
}   