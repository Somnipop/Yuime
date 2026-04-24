#pragma once

#include "../API.h"

#include "../math/vector2.h"

#include "yuime/node.h"
#include "yuime/context.h"

/**
 * @brief Default widget's window resize event.
 * @param ctx
 * @param node
 * @param ratio
 * @param delta
 */
YUIME_API void yuime_widget_on_window_resize(yuime_context_t *ctx, yuime_node_t *node, yuime_vector2_t ratio, yuime_vector2_t delta);

/**
 * @brief Default widget's resize event.
 * 
 * @param ctx
 * @param node
 */
YUIME_API void yuime_widget_on_resize(yuime_context_t *ctx, yuime_node_t *node);

/**
 * @brief Default widget's move event.
 * 
 * @param ctx 
 * @param node 
 */
YUIME_API void yuime_widget_on_move(yuime_context_t *ctx, yuime_node_t *node);