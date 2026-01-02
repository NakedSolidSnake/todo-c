#ifndef FACTORY_CONTROLLER_H
#define FACTORY_CONTROLLER_H

#include <controller_base.h>
#include <config.h>

controller_base_t *factory_controller_create (const config_t *const config);
void factory_controller_destroy (controller_base_t *const controller);

#endif /* FACTORY_CONTROLLER_H */
