#pragma once

#include <stdint.h>

uint8_t mem_alloc(void** ptr, size_t size);
uint8_t mem_realloc(void** ptr, size_t current_size, size_t size);
void mem_free(void* ptr, size_t size);

#ifndef NDEBUG
void mem_print_stats();
#endif // !NDEBUG