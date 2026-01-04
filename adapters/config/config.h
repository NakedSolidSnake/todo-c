#ifndef CONFIG_H
#define CONFIG_H

#include <sat.h>

#define CONFIG_WEBSERVER_PORT_LENGTH       6
#define CONFIG_REPOSITORY_TYPE_LENGTH      16
#define CONFIG_REPOSITORY_DATABASE_LENGTH  256
#define CONFIG_APPLICATION_MODE_LENGTH     16
#define CONFIG_APPLICATION_LANGUAGE_LENGTH 256

typedef struct
{
    struct
    {
        char port [CONFIG_WEBSERVER_PORT_LENGTH + 1];
    } webserver;

    struct 
    {
        char type [CONFIG_REPOSITORY_TYPE_LENGTH + 1];
        char database [CONFIG_REPOSITORY_DATABASE_LENGTH + 1];
    } repository;

    struct
    {
        char language [CONFIG_APPLICATION_LANGUAGE_LENGTH + 1];
        char mode [CONFIG_APPLICATION_MODE_LENGTH + 1];
    } application;

} config_t;

sat_status_t config_load (config_t *const object, const char *const file_path);

#endif /* CONFIG_H */
