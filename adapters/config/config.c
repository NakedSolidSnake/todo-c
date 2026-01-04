#include <config.h>
#include <string.h>

static void config_load_default (config_t *const object)
{
    memset (object, 0, sizeof (config_t));

    strncpy (object->webserver.port,       "1234",    CONFIG_WEBSERVER_PORT_LENGTH);
    strncpy (object->repository.type,      "memory",  CONFIG_REPOSITORY_TYPE_LENGTH);
    strncpy (object->repository.database,  "todo.db", CONFIG_REPOSITORY_DATABASE_LENGTH);
    strncpy (object->application.mode,     "cli",     CONFIG_APPLICATION_MODE_LENGTH);
    strncpy (object->application.language, "default", CONFIG_APPLICATION_LANGUAGE_LENGTH);
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
                    .group = "application",
                    .field = "language",
                    .type = sat_properties_type_string,
                    .size = CONFIG_APPLICATION_LANGUAGE_LENGTH,
                    .data = object->application.language
                },
                {
                    .group = "repository",
                    .field = "type",
                    .type = sat_properties_type_string,
                    .size = CONFIG_REPOSITORY_TYPE_LENGTH,
                    .data = object->repository.type
                },
                {
                    .group = "repository",
                    .field = "database",
                    .type = sat_properties_type_string,
                    .size = CONFIG_REPOSITORY_DATABASE_LENGTH,
                    .data = object->repository.database
                },
                {
                    .group = "webserver",
                    .field = "port",
                    .type = sat_properties_type_string,
                    .size = CONFIG_WEBSERVER_PORT_LENGTH,
                    .data = object->webserver.port
                },
            },
            .amount = 5
        };

        status = sat_properties_open (&properties, (char *)file_path);
        sat_status_break_on_error (status);

        status = sat_properties_read (&properties, &map);

    } while (false);

    return status;
}