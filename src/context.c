#include "yuime/context.h"

#include <stdlib.h>
#include <string.h>

void yuime_context_init(yuime_context_t *ctx, yuime_render_node_t render_node, const yuime_vector2_t screen_size, yuime_mem_functions_t mem_functions) {
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(yuime_context_t));
	ctx->screen_size = screen_size;
	ctx->memory = mem_functions;
	ctx->render_node = render_node;
}

void yuime_context_cleanup(yuime_context_t *ctx) {
	if (ctx == NULL)
		return;

	yuime_node_t *next_sibling;
	for (yuime_node_t *node = ctx->node_tree; node != NULL;) {
		next_sibling = node->next;

		yuime_node_free(ctx, node);

		node = next_sibling;
	}

	memset(ctx, 0, sizeof(yuime_context_t));
}