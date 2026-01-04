#include <factory_repository.h>
#include <task_repository_memory.h>
#include <task_repository_sqlite.h>
#include <string.h>

typedef task_repository_t *(*factory_repository_create_t) (const config_t *const config);

typedef struct
{    
    const char *const type;
    factory_repository_create_t create;
} factory_repository_pair_t;

static task_repository_t *factory_repository_create_memory (const config_t *const config);
static task_repository_t *factory_repository_create_sqlite (const config_t *const config);

static const factory_repository_pair_t factory_repository_pairs [] =
{
    { .type = "memory", .create = factory_repository_create_memory },
    { .type = "sqlite", .create = factory_repository_create_sqlite }
};

task_repository_t *factory_repository_create (const config_t *const config)
{
    task_repository_t *repository = NULL;

    for (size_t i = 0; i < sizeof (factory_repository_pairs) / sizeof (factory_repository_pair_t); i++)
    {
        if (strcmp (factory_repository_pairs [i].type, config->repository.type) == 0)
        {
            repository = factory_repository_pairs [i].create (config);
            break;
        }
    }

    return repository;
}

void factory_repository_destroy (task_repository_t *const repository)
{
    if (repository != NULL)
    {
        free (repository);
    }
}

static task_repository_t *factory_repository_create_memory (const config_t *const config)
{
    task_repository_memory_t *const memory = (task_repository_memory_t *const) malloc (sizeof (task_repository_memory_t));
    (void) config;

    if (memory == NULL)
    {
        return NULL;
    }

    task_repository_memory_open (memory);

    return &memory->base;
}

static task_repository_t *factory_repository_create_sqlite (const config_t *const config)
{
    task_repository_sqlite_t *const sqlite = (task_repository_sqlite_t *const) malloc (sizeof (task_repository_sqlite_t));
    sat_status_t status;

    do
    {
        sat_status_break_if_null (status, sqlite, "Failed to allocate memory for task_repository_sqlite_t");

        status = task_repository_sqlite_open (sqlite, config->repository.database);
        if (sat_status_get_result (&status) == false)
        {
            free (sqlite);
            return NULL;
        }

    } while (false);

    return &sqlite->base;
}