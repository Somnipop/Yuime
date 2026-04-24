#pragma once

#include <stdint.h>

#include "../API.h"

#include "command.h"



typedef struct yuime_render_s {
	yuime_render_command_array_t render_commands;
	yuime_render_commands_function_t render_commands_func;
	void* data;
} yuime_render_t;

// struct yuime_context_s;
// struct yuime_node_s;
// typedef yuime_children_iterate_return_signal_t(*yuime_render_node_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, void *data);


YUIME_API void yuime_render(struct yuime_context_s *ctx);