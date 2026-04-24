#pragma once

#include "API.h"

#include "math/vector2.h"

#include "node.h"
#include "context.h"

YUIME_API void yuime_event_window_resize(yuime_context_t *ctx, yuime_vector2_t screen_size);

/**
 * @brief Updates rect members according to geometry, max_size and min_size members.
 */
YUIME_API void yuime_event_resize(yuime_context_t *ctx, yuime_node_t *node);