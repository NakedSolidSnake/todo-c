#include <web_send.h>
#include <string.h>

int web_send_response (struct mg_connection *conn, const char *message, int status)
{
    sat_webserver_response_t response = {0};
    sat_webserver_response_set_status(&response, status);
    
    sat_webserver_response_set_payload (&response, (char *)message, strlen (message));
    sat_webserver_response_header_add (&response, "Content-Type", "application/json");
    
    sat_webserver_response_send (conn, response);

    return status;
}