#include <task_manager.h>
#include <string.h>

bool task_manager_open (task_manager_t *object)
{
    bool status = false;

    if (object != NULL)
    {
        sat_status_t __status = sat_array_create (&object->tasks, &(sat_array_args_t)
                                                                    {   
                                                                        .size = DEFINITIONS_TASKS_MAX,
                                                                        .object_size = sizeof (task_t),
                                                                        .mode = sat_array_mode_static
                                                                    });
        status = sat_status_get_result (&__status);
    }

    return status;
}

bool task_manager_add (task_manager_t *object, task_t *task)
{
    bool status = false;

    if (object != NULL && task != NULL)
    {
        sat_status_t __status = sat_array_add (object->tasks, (void *)task);

        status = sat_status_get_result (&__status);
    }

    return status;
}

bool task_manager_get_by (task_manager_t *object, uint32_t index, task_t *task)
{
    bool status = false;

    if (object != NULL && task != NULL)
    {
        memset (task, 0, sizeof (task_t));

        sat_status_t __status = sat_array_get_object_by (object->tasks, index, (void *)task);

        status = sat_status_get_result (&__status);
    }

    return status;
}

bool task_manager_find_by (task_manager_t *object, uint32_t id, task_t *task, uint32_t *index)
{
    bool status = false;

    if (object != NULL && task != NULL && index != NULL)
    {
        uint32_t size;

        sat_array_get_size (object->tasks, &size);

        for (uint32_t i = 0; i < size; i++)
        {
            sat_array_get_object_by (object->tasks, i, (void *)task);

            if (task->id == id)
            {
                *index = i;
                status = true;
                break;
            }
        }
    }

    return status;
}

bool task_manager_update_by (task_manager_t *object, uint32_t index, task_t *task)
{
    bool status = false;

    if (object != NULL && task != NULL)
    {
        sat_status_t __status = sat_array_update_by (object->tasks, task, index);

        status = sat_status_get_result (&__status);
    }

    return status;
}

bool task_manager_remove_by (task_manager_t *object, uint32_t index)
{
    bool status = false;

    if (object != NULL)
    {
        sat_status_t __status = sat_array_remove_by (object->tasks, index);

        status = sat_status_get_result (&__status);
    }

    return status;
}

bool task_manager_close (task_manager_t *object)
{
    bool status = false;

    if (object != NULL)
    {
        sat_status_t __status = sat_array_destroy (object->tasks);

        status = sat_status_get_result (&__status);
    }

    return status;
}

uint32_t task_manager_get_tasks_amount (task_manager_t *object)
{
    uint32_t amount = 0;

    if (object != NULL)
    {
        sat_array_get_size (object->tasks, &amount);        
    }

    return amount;
}