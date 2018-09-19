/**
 * @file home_base_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_HOME_BASE_PARAMS_H_
#define PROJECT_ITERATION1_SRC_HOME_BASE_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
struct home_base_params : public arena_mobile_entity_params {
  home_base_params(void) :
      arena_mobile_entity_params(),
      angle_delta_() {}

  uint angle_delta_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_HOME_BASE_PARAMS_H_
