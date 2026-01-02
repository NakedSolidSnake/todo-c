#include <factory_repository.h>
#include <task_repository_memory.h>
#include <string.h>

typedef task_repository_t *(*factory_repository_create_t) (void);

typedef struct
{    
    const char *const type;
    factory_repository_create_t create;
} factory_repository_pair_t;

static task_repository_t *factory_repository_create_memory (void);
// static task_repository_t *factory_repository_create_file (void);

static const factory_repository_pair_t factory_repository_pairs [] =
{
    { .type = "memory", .create = factory_repository_create_memory },
    // { .type = "file", .create = factory_repository_create_file }
};

task_repository_t *factory_repository_create (const config_t *const config)
{
    task_repository_t *repository = NULL;

    for (size_t i = 0; i < sizeof (factory_repository_pairs) / sizeof (factory_repository_pair_t); i++)
    {
        if (strcmp (factory_repository_pairs [i].type, config->repository.type) == 0)
        {
            repository = factory_repository_pairs [i].create ();
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

static task_repository_t *factory_repository_create_memory (void)
{
    task_repository_memory_t *const memory = (task_repository_memory_t *const) malloc (sizeof (task_repository_memory_t));

    if (memory == NULL)
    {
        return NULL;
    }

    task_repository_memory_open (memory);

    return &memory->base;
}