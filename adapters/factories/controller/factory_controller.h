#ifndef FACTORY_CONTROLLER_H
#define FACTORY_CONTROLLER_H

#include <controller_base.h>

controller_base_t *factory_controller_create (const char *const type);
void factory_controller_destroy (controller_base_t *const controller);

#endif /* FACTORY_CONTROLLER_H */
