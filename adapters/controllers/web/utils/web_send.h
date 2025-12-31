#ifndef WEB_SEND_H
#define WEB_SEND_H

#include <sat.h>

int web_send_response (struct mg_connection *conn, const char *message, int status);

#endif /* WEB_SEND_H */
