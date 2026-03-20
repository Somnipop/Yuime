#include "yuime/base/context.h"

#include <stdlib.h>
#include <string.h>

void yuime_context_init(yuime_context *ctx, yuime_memory_functions mem_functions, yuime_render_callback render) {
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(yuime_context));
	ctx->memory = mem_functions;
	ctx->render = render;

	yuime_element_array_init(&ctx->memory, &ctx->elements, 0);
}

yuime_element *yuime_context_element_add(yuime_context *ctx, const yuime_element *element) {
	yuime_element_array_push(&ctx->memory, &ctx->elements, element);
	// No need to check if push succeeded before because get already checks if index and data are valid.
	return yuime_element_array_get(&ctx->elements, ctx->elements.count-1);
}