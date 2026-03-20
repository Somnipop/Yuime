#include "mem_alloc.h"

#include <stdlib.h>
#ifndef NDEBUG
#include <stdio.h>
#endif // !NDEBUG

uint8_t mem_alloc(void** ptr, size_t size) {
	*ptr = malloc(size);

	if (*ptr) {
#ifndef NDEBUG
		printf("Allocated %zu bytes\n", size);
#endif // !NDEBUG
		return 1;

	} else {
#ifndef NDEBUG
		printf("Failed to allocate %zu bytes\n", size);
#endif // !NDEBUG
		return 0;
	}
}

uint8_t mem_realloc(void** ptr, size_t current_size, size_t size) {
	void* new_ptr = realloc(*ptr, size);

	if (new_ptr) {
		*ptr = new_ptr;
#ifndef NDEBUG
		printf("Re-allocated from %zu to %zu bytes\n", current_size, size);
#endif // !NDEBUG
		return 1;

	} else {
#ifndef NDEBUG
		printf("Failed to re-allocate from %zu to %zu bytes\n", current_size, size);
#endif // !NDEBUG
		return 0;
	}
}

void mem_free(void* ptr, size_t size) {
	free(ptr);
#ifndef NDEBUG
		printf("Freed %zu bytes\n", size);
#endif // !NDEBUG
}