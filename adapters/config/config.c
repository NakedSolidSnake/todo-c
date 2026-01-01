#include <config.h>
#include <string.h>

static void config_load_default (config_t *const object)
{
    memset (object, 0, sizeof (config_t));

    strncpy (object->webserver.port, "1234", CONFIG_WEBSERVER_PORT_LENGTH);
    strncpy (object->repository.type, "memory", CONFIG_REPOSITORY_TYPE_LENGTH);
    strncpy (object->cli.idiom_file, "default", CONFIG_CLI_IDIOM_FILE_PATH_LENGTH);
    strncpy (object->application.mode, "cli", CONFIG_APPLICATION_MODE_LENGTH);
}

sat_status_t config_load (config_t *const object, const char *const file_path)
{
    sat_status_t status;
    sat_properties_t properties;

    do
    {
        sat_status_break_if_null (status, object, "config_t is null");

        config_load_default (object);

        sat_properties_map_t map = 
        {
            .items = 
            {
                {
                    .group = "application",
                    .field = "mode",
                    .type = sat_properties_type_string,
                    .size = CONFIG_APPLICATION_MODE_LENGTH,
                    .data = object->application.mode
                },
                {
                    .group = "repository",
                    .field = "type",
                    .type = sat_properties_type_string,
                    .size = CONFIG_REPOSITORY_TYPE_LENGTH,
                    .data = object->repository.type
                },
                {
                    .group = "webserver",
                    .field = "port",
                    .type = sat_properties_type_string,
                    .size = CONFIG_WEBSERVER_PORT_LENGTH,
                    .data = object->webserver.port
                },
                {
                    .group = "cli",
                    .field = "idiom",
                    .type = sat_properties_type_string,
                    .size = CONFIG_CLI_IDIOM_FILE_PATH_LENGTH,
                    .data = object->cli.idiom_file
                },
            },
            .amount = 4
        };

        status = sat_properties_open (&properties, (char *)file_path);
        sat_status_break_on_error (status);

        status = sat_properties_read (&properties, &map);

    } while (false);

    return status;
}