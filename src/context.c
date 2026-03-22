#include "yuime/context.h"

#include <stdlib.h>
#include <string.h>

void yuime_context_init(yuime_context_t *ctx, const yuime_vector2_t screen_size, yuime_mem_functions_t mem_functions) {
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(yuime_context_t));
	ctx->screen_size = screen_size;
	ctx->memory = mem_functions;
}

void yuime_context_cleanup(yuime_context_t *ctx) {
	if (ctx == NULL)
		return;

	// TODO: yuime_node_tree_cleanup();
	// for (yuime_element_pointer_array_index_t i = 0; i < ctx->elements.count; i++) {
	// 	if (ctx->elements.data[i]->free) {
	// 		ctx->elements.data[i]->free(ctx->elements.data[i]);
	// 	}
	//}

	memset(ctx, 0, sizeof(yuime_context_t));
}