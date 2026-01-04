#include <task_repository_sqlite.h>
#include <string.h>

static const char *const sql_insert_task =
    "INSERT INTO tasks_tb (name, description, completed, deleted) "
    "VALUES ('%s', '%s', %d, 0);";

static const char *const sql_find_by_name = 
    "SELECT name FROM tasks_tb "
    "WHERE name = '%s'";

static const char *const sql_find_by_id = 
    "SELECT id, name, description, completed FROM tasks_tb "
    "WHERE id = %d AND deleted = 0;";

static const char *const sql_remove_by_id = 
    "UPDATE tasks_tb SET deleted = 1 "
    "WHERE id = %d;";

static const char *const sql_complete_by_id = 
    "UPDATE tasks_tb SET completed = 1 "
    "WHERE id = %d;";

static const char *const sql_select_all = 
    "SELECT id, name, description, completed FROM tasks_tb "
    "WHERE deleted = 0;";

static const char *const sql_update_task = 
    "UPDATE tasks_tb SET name = '%s', description = '%s', completed = %d "
    "WHERE id = %d";

static const char *const sql_select_count = 
    "SELECT COUNT(*) FROM tasks_tb "
    "WHERE deleted = 0;";



static sat_status_t task_repository_sqlite_store (void *const object, const task_t *const task);
static sat_status_t task_repository_sqlite_find_by_id (void *const object, const uint32_t id, task_t *const task);
static sat_status_t task_repository_sqlite_find_by_name (void *const object, const char *const name, task_t *const task);
static sat_status_t task_repository_sqlite_remove_by_id (void *const object, const uint32_t id);
static sat_status_t task_repository_sqlite_complete_by_id (void *const object, const uint32_t id);
static sat_status_t task_repository_sqlite_update (void *const object, const task_t *const task);
static sat_status_t task_repository_sqlite_get_all (void *const object, sat_array_t **const tasks);

static sat_status_t task_repository_sqlite_create_database (sat_sqlite_t *const object);
static uint32_t task_repository_sqlite_get_tasks_count (task_repository_sqlite_t *const object);

static int task_repository_sqlite_on_count_result_set (void *user, int columns, char **data, char **names);
static int task_repository_sqlite_on_get_all_result_set (void *user, int columns, char **data, char **names);
static int task_repository_sqlite_on_find_by_name_result_set (void *user, int columns, char **data, char **names);
static int task_repository_sqlite_on_find_by_id_result_set (void *user, int columns, char **data, char **names);

sat_status_t task_repository_sqlite_open (task_repository_sqlite_t *const object, const char *const filename)
{
    sat_status_t status = sat_status_success (&status);

    do
    {
        sat_status_break_if_null (status, object, "task_repository_sqlite_t is null");

        memset (object, 0, sizeof (task_repository_sqlite_t));

        status = sat_sqlite_init (&object->handle);
        sat_status_break_on_error (status);

        status = sat_sqlite_open (&object->handle, &(sat_sqlite_args_t)
                                                    {
                                                        .database = filename,
                                                    });
        sat_status_break_on_error (status);

        status = task_repository_sqlite_create_database (&object->handle);
        sat_status_break_on_error (status);

        // Set up function pointers
        object->base.object = object;
        object->base.store = task_repository_sqlite_store;
        object->base.find_by_id = task_repository_sqlite_find_by_id;
        object->base.find_by_name = task_repository_sqlite_find_by_name;
        object->base.remove_by_id = task_repository_sqlite_remove_by_id;
        object->base.complete_by_id = task_repository_sqlite_complete_by_id;
        object->base.update = task_repository_sqlite_update;
        object->base.get_all = task_repository_sqlite_get_all;

    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_store (void *const object, const task_t *const task)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");
        sat_status_break_if_null (status, task, "task_t is null");

        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_insert_task, task->name, task->description, task->done ? 1 : 0);

        status = sat_sqlite_execute (&sqlite->handle, sql, NULL, NULL);
        
    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_find_by_id (void *const object, const uint32_t id, task_t *const task)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");
        sat_status_break_if_null (status, task, "task_t is null");

        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_find_by_id, id);

        status = sat_sqlite_execute (&sqlite->handle, sql, task_repository_sqlite_on_find_by_id_result_set, task);
        sat_status_break_on_error (status);

        if (task->id != id)
        {
            sat_status_failure (&status, "Task not found");
            break;
        }

        sat_status_success (&status);

    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_find_by_name (void *const object, const char *const name, task_t *const task)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");
        sat_status_break_if_null (status, name, "name is null");
        sat_status_break_if_null (status, task, "task_t is null");

        char __name [256] = {0};
        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_find_by_name, name);

        status = sat_sqlite_execute (&sqlite->handle, sql, task_repository_sqlite_on_find_by_name_result_set, __name);

        if (strcmp (name, __name) == 0)
        {            
            break;
        }
        
        sat_status_failure (&status, "Task not found");

    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_remove_by_id (void *const object, const uint32_t id)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");

        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_remove_by_id, id);

        status = sat_sqlite_execute (&sqlite->handle, sql, NULL, NULL);
        sat_status_break_on_error (status);

        task_t task;

        status = task_repository_sqlite_find_by_id (object, id, &task);
        sat_status_break_on_error (status);

        if (task.id == id)
        {
            sat_status_failure (&status, "Failed to remove task");
            break;
        }

    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_complete_by_id (void *const object, const uint32_t id)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");

        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_complete_by_id, id);

        status = sat_sqlite_execute (&sqlite->handle, sql, NULL, NULL);


    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_update (void *const object, const task_t *const task)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");
        sat_status_break_if_null (status, task, "task_t is null");

        char sql [512] = {0};
        snprintf (sql, sizeof (sql) - 1, sql_update_task, task->name, task->description, task->done ? 1 : 0, task->id);

        status = sat_sqlite_execute (&sqlite->handle, sql, NULL, NULL);

    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_get_all (void *const object, sat_array_t **const tasks)
{
    sat_status_t status;
    task_repository_sqlite_t *sqlite = (task_repository_sqlite_t *) object;

    do
    {
        sat_status_break_if_null (status, sqlite, "task_repository_sqlite_t is null");

        uint32_t count = task_repository_sqlite_get_tasks_count (sqlite);
        sat_status_break_if_equals (status, count, 0, "No tasks found");

        status = sat_array_create (tasks,  &(sat_array_args_t)
                                            {
                                                .size = count,
                                                .object_size = sizeof (task_t),
                                                .mode = sat_array_mode_static,
                                            });
        sat_status_break_on_error (status);

        status = sat_sqlite_execute (&sqlite->handle, sql_select_all, task_repository_sqlite_on_get_all_result_set, *tasks);


    } while (false);

    return status;
}

static sat_status_t task_repository_sqlite_create_database (sat_sqlite_t *const object)
{
    const char *create_table_sql =
            "CREATE TABLE IF NOT EXISTS tasks_tb ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"
            "description TEXT NOT NULL,"
            "completed INTEGER NOT NULL DEFAULT 0,"
            "deleted INTEGER NOT NULL DEFAULT 0"
            ");";
        
    return sat_sqlite_execute (object, create_table_sql, NULL, NULL);
}

static uint32_t task_repository_sqlite_get_tasks_count (task_repository_sqlite_t *const object)
{
    uint32_t count = 0;
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, object, "task_repository_sqlite_t is null");

        status = sat_sqlite_execute (&object->handle, sql_select_count, task_repository_sqlite_on_count_result_set, &count);

    } while (false);

    return count;
}

static int task_repository_sqlite_on_count_result_set (void *user, int columns, char **data, char **names)
{
    uint32_t *count = (uint32_t *)user;
    *count = (uint32_t)atoi (data [0]);
    return 0;
}

static int task_repository_sqlite_on_get_all_result_set (void *user, int columns, char **data, char **names)
{
    sat_array_t *tasks = (sat_array_t *) user;
    task_t task;

    memset (&task, 0, sizeof (task_t));

    uint32_t id = (uint32_t)atoi (data [0]);

    task_create_with_id (&task, id, data [1], data [2]);

    sat_array_add (tasks, &task);

    return 0;
}

static int task_repository_sqlite_on_find_by_name_result_set (void *user, int columns, char **data, char **names)
{
    char *name = (char *)user;

    strncpy (name, data [0], 255);

    return 0;
}

static int task_repository_sqlite_on_find_by_id_result_set (void *user, int columns, char **data, char **names)
{
    task_t *task = (task_t *)user;

    uint32_t id = (uint32_t)atoi (data [0]);

    task_create_with_id (task, id, data [1], data [2]);
    task->done = (strcmp (data [3], "1") == 0) ? true : false;

    return 0;
}