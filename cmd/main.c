#include <cli.h>
#include <task_repository_memory.h>

int main (void)
{
    cli_t cli;
    sat_status_t status;
    task_repository_memory_t memory;

    sat_log_init_by_env ("error");

    do
    {
        status = task_repository_memory_open (&memory);
        sat_status_break_on_error (status);

        status = cli_init (&cli);
        sat_status_break_on_error (status);

        status = cli.base.open (&cli, &(cli_args_t){.repository = &memory.base});
        sat_status_break_on_error (status);

        status = cli.base.run (&cli);
        sat_status_break_on_error (status);

        status = cli.base.close (&cli);
        sat_status_break_on_error (status);

    } while (false);

    printf ("%s\n", sat_status_get_motive (&status));

    return 0;
}