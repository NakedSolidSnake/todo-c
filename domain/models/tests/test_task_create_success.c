#include <assert.h>
#include <task.h>

int main (void)
{
    task_t task;
    sat_status_t status = task_create (&task, "Test Task", "This is a test task description.");
    assert (sat_status_get_result (&status) == true);
    return 0;
}
