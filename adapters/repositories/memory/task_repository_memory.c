#include <task_repository_memory.h>
#include <string.h>

static bool task_repository_memory_is_equal (const void *const a, const void *const b)
{
    const task_t *task_a = (const task_t *) a;
    const task_t *task_b = (const task_t *) b;

    return (strcmp (task_a->name, task_b->name) == 0);
}

static bool task_repository_memory_compare_name (const void *const element, const void *const param)
{
    const task_t *task_element = (const task_t *) element;
    const char *name = (const char *) param;

    return (strcmp (task_element->name, name) == 0);
}

static bool task_repository_memory_compare_id (const void *const element, const void *const param)
{
    const task_t *task_element = (const task_t *) element;
    const uint32_t *id = (const uint32_t *) param;

    return (task_element->id == *id);
}

static sat_status_t task_repository_memory_store (void *const object, const task_t *const task);
static sat_status_t task_repository_memory_find_by_name (void *const object, const char *const name, task_t *const task);
static sat_status_t task_repository_memory_remove_by_id (void *const object, const uint32_t id);
static sat_status_t task_repository_memory_complete_by_id (void *const object, const uint32_t id);
static sat_status_t task_repository_memory_update (void *const object, const task_t *const task);

sat_status_t task_repository_memory_open (task_repository_memory_t *const object)
{
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "task_repository_memory_t is null");

        status = sat_set_create (&object->storage, &(sat_set_args_t)
                                                    {
                                                        .size = 10,
                                                        .object_size = sizeof (task_t),
                                                        .is_equal = task_repository_memory_is_equal,
                                                        .mode = sat_set_mode_static
                                                    });
        sat_status_break_on_error (status);

        object->base.object = object;
        object->base.store = task_repository_memory_store;
        object->base.find_by_name = task_repository_memory_find_by_name;
        object->base.remove_by_id = task_repository_memory_remove_by_id;
        object->base.complete_by_id = task_repository_memory_complete_by_id;
        object->base.update = task_repository_memory_update;

    } while (false);

    return status;
}

static sat_status_t task_repository_memory_store (void *const object, const task_t *const task)
{
    sat_status_t status;
    task_repository_memory_t *memory = (task_repository_memory_t *) object;

    do
    {
        sat_status_break_if_null (status, memory, "task_repository_memory_t is null");
        sat_status_break_if_null (status, task, "task_t is null");

        status = sat_set_add (memory->storage, (void *) task);

    } while (false);

    return status;
}

static sat_status_t task_repository_memory_find_by_name (void *const object, const char *const name, task_t *const task)
{
    sat_status_t status;
    task_repository_memory_t *memory = (task_repository_memory_t *) object;

    do
    {
        sat_status_break_if_null (status, memory, "task_repository_memory_t is null");
        sat_status_break_if_null (status, name, "name is null");
        sat_status_break_if_null (status, task, "task_t is null");

        status = sat_set_get_object_by_parameter (memory->storage,
                                           (void *) name,
                                           task_repository_memory_compare_name,
                                           (void *) task);

    } while (false);

    return status;
}

static sat_status_t task_repository_memory_remove_by_id (void *const object, const uint32_t id)
{
    sat_status_t status;
    task_repository_memory_t *memory = (task_repository_memory_t *) object;

    do
    {
        sat_status_break_if_null (status, memory, "task_repository_memory_t is null");
        
        status = sat_set_remove_by_parameter (memory->storage,
                                      (void *) &id,
                                      task_repository_memory_compare_id,
                                      NULL);

    } while (false);

    return status;
}

static sat_status_t task_repository_memory_complete_by_id (void *const object, const uint32_t id)
{
    sat_status_t status;
    task_repository_memory_t *memory = (task_repository_memory_t *) object;

    do
    {
        sat_status_break_if_null (status, memory, "task_repository_memory_t is null");

        task_t *task;

        status = sat_set_get_object_ref_by_parameter (memory->storage,
                                                 (void *) &id,
                                                 task_repository_memory_compare_id,
                                                 (void **) &task);
        sat_status_break_on_error (status);

        status = task_set_done (task, true);

    } while (false);

    return status;
}

static sat_status_t task_repository_memory_update (void *const object, const task_t *const task)
{
    sat_status_t status;
    task_repository_memory_t *memory = (task_repository_memory_t *) object;

    do
    {
        sat_status_break_if_null (status, memory, "task_repository_memory_t is null");
        sat_status_break_if_null (status, task, "task_t is null");

        task_t *task_ref;

        status = sat_set_get_object_ref_by_parameter (memory->storage,
                                                 (void *) &task->id,
                                                 task_repository_memory_compare_id,
                                                 (void **) &task_ref);
        sat_status_break_on_error (status);

        status = task_update (task_ref, task->name, task->description);

    } while (false);

    return status;
}

