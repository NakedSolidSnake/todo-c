#include <handler_health.h>
#include <string.h>
#include <web_send.h>

int handler_health (struct mg_connection *conn, void *data)
{
    char *json_response = "{"
                            "\"message\": \"Hello from Todo Webserver!\","
                            "\"endpoint\": \"/health\","
                            "\"status\": \"active\""
                            "}";
    
    return web_send_response (conn, json_response, sat_webserver_http_status_ok);
}