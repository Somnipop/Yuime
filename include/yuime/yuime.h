#pragma once

#include "API.h"

#include "base/math/vector2.h"
#include "base/math/rect.h"
#include "base/math/dimension2.h"
#include "base/math/geometry.h"

#include "base/element/element.h"
#include "base/element/array.h"
#include "base/element/pointer_array.h"

#include "base/context.h"
#include "base/event.h"

#include "base/alloc.h"

#ifndef YUIME_BUILD_BASE_ONLY
#include "elements/type.h"
#include "elements/button.h"
#endif // !YUIME_BUILD_BASE_ONLY

#include "util.h"

/**
 * 
 * @brief Sets visibility of element.
 * 
 * This function MUST BE CALLED instead of settings flags manually, since it checks for parents as well.
 * 
 * @param element 
 * @param visible 
 */
YUIME_API void yuime_set_visibility(const yuime_memory_functions_t *mem_funcs, yuime_element_t *element, uint8_t visible);

YUIME_API void yuime_update(yuime_context_t *ctx);
YUIME_API void yuime_render(yuime_context_t *ctx);