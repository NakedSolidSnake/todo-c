#include <todo_factory.h>
#include <task_repository_memory.h>

int main (void)
{
    sat_status_t status;
    task_repository_memory_t memory;

    sat_log_init_by_env ("error");

    do
    {
        status = task_repository_memory_open (&memory);
        sat_status_break_on_error (status);

        controller_base_t *controller = todo_factory_create_controller (todo_factory_type_cli);
        sat_status_break_on_error (status);

        status = controller->open (controller, &(controller_base_args_t){.repository = &memory.base});
        sat_status_break_on_error (status);

        status = controller->run (controller);
        sat_status_break_on_error (status);

        status = controller->close (controller);
        sat_status_break_on_error (status);

    } while (false);

    printf ("%s\n", sat_status_get_motive (&status));

    return 0;
}