#ifndef FACTORY_REPOSITORY_H
#define FACTORY_REPOSITORY_H

#include <task_repository.h>
#include <config.h>

task_repository_t *factory_repository_create (const config_t *const config);
void factory_repository_destroy (task_repository_t *const repository);

#endif /* FACTORY_REPOSITORY_H */
