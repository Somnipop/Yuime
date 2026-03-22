#pragma once

#include "API.h"

#include "alloc.h"

#include "math/vector2.h"
#include "math/rect.h"
#include "math/dimension2.h"
#include "math/geometry.h"

#include "node.h"

#include "context.h"

/**
 * 
 * @brief Sets visibility of element.
 * 
 * This function MUST BE CALLED instead of settings flags manually, since it checks for parents as well.
 * 
 * @param element 
 * @param visible 
 */
// TODO: YUIME_API void yuime_set_visibility(const yuime_mem_functions_t *mem_funcs, yuime_node_t *element, uint8_t visible);

// YUIME_API void yuime_update(yuime_context_t *ctx);
// YUIME_API void yuime_render(yuime_context_t *ctx);