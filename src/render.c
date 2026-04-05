#include "yuime/render.h"

#include "yuime/context.h"

void yuime_render(yuime_context_t *ctx) {
	yuime_node_t *node = ctx->node_tree;
	while (node != NULL) {
		if (ctx->render_node(ctx, node, NULL) != 0) {
			node = node->next;
			continue;
		}

		yuime_node_iterate_children_parent_first(ctx, node, ctx->render_node, NULL);

		node = node->next;
	}
}