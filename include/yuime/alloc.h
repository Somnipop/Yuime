#pragma once

#include <stdint.h>

#include "API.h"

typedef uint8_t(*yuime_mem_alloc_t)(void* ptr, size_t size);
typedef uint8_t(*yuime_mem_realloc_t)(void* ptr, size_t size);
typedef void(*yuime_mem_free_t)(void* ptr);

typedef struct yuime_mem_functions_s {
	yuime_mem_alloc_t alloc;
	yuime_mem_realloc_t realloc;
	yuime_mem_free_t free;
} yuime_mem_functions;