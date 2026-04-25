#pragma once

#include <stdint.h>

#include "API.h"

typedef uint8_t yuime_alloc_context_t;
enum yuime_alloc_context_e {
	YUIME_ALLOC_CONTEXT_UNKNOWN = 0,
	YUIME_ALLOC_CONTEXT_NODE,
	YUIME_ALLOC_CONTEXT_WIDGET,
	YUIME_ALLOC_CONTEXT_RENDER_COMMAND,
	YUIME_ALLOC_CONTEXT_COUNT
};

// should return 0 if failed
typedef uint8_t(*yuime_mem_alloc_t)(yuime_alloc_context_t ctx, void** ptr, size_t size);
// should return 0 if failed
typedef uint8_t(*yuime_mem_realloc_t)(yuime_alloc_context_t ctx, void** ptr, size_t current_size, size_t size);
typedef void(*yuime_mem_free_t)(yuime_alloc_context_t ctx, void *ptr, size_t size);

typedef struct yuime_mem_functions_s {
	yuime_mem_alloc_t alloc;
	yuime_mem_realloc_t realloc;
	yuime_mem_free_t free;
} yuime_mem_functions_t;