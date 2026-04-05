#pragma once

#include <stdint.h>

#include "API.h"

#include "node.h"

struct yuime_context_s;

// Return anything that is not 0 and it will not render its children
typedef yuime_children_iterate_return_signal_t(*yuime_render_node_t)(struct yuime_context_s *ctx, yuime_node_t *node, void* data);

YUIME_API void yuime_render(struct yuime_context_s *ctx);