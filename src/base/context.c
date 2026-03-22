#include "yuime/base/context.h"

#include <stdlib.h>
#include <string.h>

void yuime_context_init(yuime_context_t *ctx, const yuime_vector2_t screen_size, yuime_memory_functions_t mem_functions, yuime_render_callback_t render) {
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(yuime_context_t));
	ctx->screen_size = screen_size;
	ctx->memory = mem_functions;
	ctx->render = render;

	yuime_element_pointer_array_init(&ctx->memory, &ctx->elements, 0);
}

void yuime_context_cleanup(yuime_context_t *ctx) {
	if (ctx == NULL)
		return;

	for (yuime_element_pointer_array_index_t i = 0; i < ctx->elements.count; i++) {
		if (ctx->elements.data[i]->free) {
			ctx->elements.data[i]->free(ctx->elements.data[i]);
		}
	}

	yuime_element_pointer_array_free(&ctx->memory, &ctx->elements);
	memset(ctx, 0, sizeof(yuime_context_t));
}

uint8_t yuime_context_element_add(yuime_context_t *ctx, yuime_element_t *element) {
	return yuime_element_pointer_array_push(&ctx->memory, &ctx->elements, element);
}