#include <web_response.h>
#include <stdio.h>
#include <string.h>

static char response [512];

const char *const web_response_create (bool type, const char *const message)
{
    const char *response_template_error = 
    "{"
        "\"status\": \"error\","
        "\"message\": \"%s\""
    "}";
    
    const char *response_template_success = 
    "{"
        "\"status\": \"success\","
        "\"message\": \"%s\""
    "}";

    memset (response, 0, sizeof (response));

    if (type == false)
    {
        snprintf (response, sizeof (response), response_template_error, message);
    }
    else // web_response_type_success
    {
        snprintf (response, sizeof (response), response_template_success, message);
    }

    return response;
}