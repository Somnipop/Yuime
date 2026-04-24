#pragma once

#include <stdint.h>

#include <yuime/alloc.h>

uint8_t mem_alloc(yuime_alloc_context_t ctx, void** ptr, size_t size);
uint8_t mem_realloc(yuime_alloc_context_t ctx, void** ptr, size_t current_size, size_t size);
void mem_free(yuime_alloc_context_t ctx, void* ptr, size_t size);

#ifndef NDEBUG
void mem_print_stats();
#endif // !NDEBUG