#ifndef CONFIG_H
#define CONFIG_H

#include <sat.h>

#define CONFIG_WEBSERVER_PORT_LENGTH      6
#define CONFIG_REPOSITORY_TYPE_LENGTH     16
#define CONFIG_CLI_IDIOM_FILE_PATH_LENGTH 256
#define CONFIG_APPLICATION_MODE_LENGTH    16

typedef struct
{
    struct
    {
        char port [CONFIG_WEBSERVER_PORT_LENGTH + 1];
    } webserver;

    struct 
    {
        char type [CONFIG_REPOSITORY_TYPE_LENGTH + 1];
    } repository;

    struct 
    {
        char idiom_file [CONFIG_CLI_IDIOM_FILE_PATH_LENGTH + 1];
    } cli;

    struct
    {
        char mode [CONFIG_APPLICATION_MODE_LENGTH + 1];
    } application;

} config_t;

sat_status_t config_load (config_t *const object, const char *const file_path);

#endif /* CONFIG_H */
