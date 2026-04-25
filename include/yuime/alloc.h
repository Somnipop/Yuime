#pragma once

#include <stdint.h>

#include "API.h"

#define _YUIME_ALLOC_CONTEXT_LIST(X) \
	X(YUIME_ALLOC_CONTEXT_UNKNOWN, 0, "Unknown") \
	X(YUIME_ALLOC_CONTEXT_NODE, 1, "Node") \
	X(YUIME_ALLOC_CONTEXT_WIDGET, 2, "Widget") \
	X(YUIME_ALLOC_CONTEXT_RENDER_COMMAND, 3, "Render Command")

#define _YUIME_ALLOC_CONTEXT_LIST_TO_ENUM(var, id, name) var = id,
typedef uint8_t yuime_alloc_context_t;
enum yuime_alloc_context_e {
	_YUIME_ALLOC_CONTEXT_LIST(_YUIME_ALLOC_CONTEXT_LIST_TO_ENUM)
	YUIME_ALLOC_CONTEXT_COUNT
};
#undef _YUIME_ALLOC_CONTEXT_LIST_TO_ENUM

// Should return 0 if failed.
typedef uint8_t(*yuime_mem_alloc_t)(yuime_alloc_context_t ctx, void** ptr, size_t size);
// Should return 0 if failed.
typedef uint8_t(*yuime_mem_realloc_t)(yuime_alloc_context_t ctx, void** ptr, size_t current_size, size_t new_size);
typedef void(*yuime_mem_free_t)(yuime_alloc_context_t ctx, void *ptr, size_t size);

typedef struct yuime_mem_functions_s {
	yuime_mem_alloc_t alloc;
	yuime_mem_realloc_t realloc;
	yuime_mem_free_t free;
} yuime_mem_functions_t;