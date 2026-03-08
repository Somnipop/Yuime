#include "yuime/context.h"

#include <stdlib.h>
#include <string.h>

void yuime_context_init(yuime_context* ctx, yuime_mem_functions mem_functions) {
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(yuime_context));

	ctx->memory.alloc = mem_functions.alloc;
	ctx->memory.realloc = mem_functions.realloc;
	ctx->memory.free = mem_functions.free;

	yuime_element_array_init(&ctx->memory, &ctx->elements, 0);
}

yuime_element* yuime_context_element_add(yuime_context* ctx, yuime_element element) {
	yuime_element_array_push(&ctx->memory, &ctx->elements, &element);
	// No need to check if push succeeded before because get already checks if index and data are valid.
	return yuime_element_array_get(&ctx->elements, ctx->elements.count-1);
}