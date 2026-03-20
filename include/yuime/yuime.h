#pragma once

#include "API.h"

#include "base/vector2.h"
#include "base/rect.h"
#include "base/dimension2.h"
#include "base/geometry.h"

#include "base/context.h"
#include "base/event.h"
#include "base/element.h"
#include "base/element_array.h"
#include "base/element_pointer_array.h"

#include "base/alloc.h"

#ifndef YUIME_BUILD_BASE_ONLY
#include "elements/type.h"
#include "elements/button.h"
#endif // !YUIME_BUILD_BASE_ONLY

/**
 * @brief Sets visibility of element.
 * 
 * This function MUST BE CALLED instead of settings flags manually, since it checks for parents as well.
 * 
 * @param element 
 * @param visible
 */
YUIME_API void yuime_set_visibility(const yuime_memory_functions *mem_funcs, yuime_element *element, uint8_t visible);

YUIME_API void yuime_update(yuime_context *ctx);
YUIME_API void yuime_draw(yuime_context *ctx);