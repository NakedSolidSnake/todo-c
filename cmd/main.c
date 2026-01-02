#include <factory_controller.h>
#include <factory_repository.h>
#include <config.h>

int main (int argc, char *argv [])
{
    sat_status_t status;
    config_t config;

    sat_log_init_by_env ("error");

    do
    {
        if (argc != 2)
        {
            printf ("Usage: %s <config_file_path>\n", argv [0]);
            sat_status_failure (&status, "Invalid number of arguments.");
            break;
        }

        status = config_load (&config, argv[1]);
        sat_status_break_on_error (status);

        task_repository_t *repository = factory_repository_create (&config);
        sat_status_break_if_null (status, repository, "Failed to create repository from factory.");

        // controller_base_t *controller = factory_controller_create (factory_controller_type_cli);
        controller_base_t *controller = factory_controller_create (&config);
        sat_status_break_on_error (status);

        status = controller->open (controller, &(controller_base_args_t)
                                                {
                                                   .repository = repository,
                                                   .config = &config
                                                });
        sat_status_break_on_error (status);

        status = controller->run (controller);
        sat_status_break_on_error (status);

        status = controller->close (controller);
        sat_status_break_on_error (status);

    } while (false);

    printf ("%s\n", sat_status_get_motive (&status));

    return 0;
}