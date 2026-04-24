#include "yuime/render/render.h"

#include "yuime/context.h"

void yuime_render(struct yuime_context_s *ctx) {
	ctx->render.render_commands_func(ctx);

	// yuime_node_t *node = ctx->node_tree;
	// while (node != NULL) {
	// 	if (ctx->render.node(ctx, node, NULL) != 0) {
	// 		node = node->next;
	// 		continue;
	// 	}

	// 	yuime_node_iterate_children_parent_first(ctx, node, ctx->render.node, NULL);

	// 	node = node->next;
	// }
}