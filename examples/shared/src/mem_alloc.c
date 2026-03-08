#include "mem_alloc.h"

#include <stdlib.h>
#include <stdio.h>

uint8_t mem_alloc(void** ptr, size_t size) {
	*ptr = malloc(size);

	if (*ptr) {
		printf("Allocated %zu bytes\n", size);
		return 1;

	} else {
		printf("Failed to allocate %zu bytes\n", size);
		return 0;
	}
}

uint8_t mem_realloc(void** ptr, size_t current_size, size_t size) {
	void* new_ptr = realloc(*ptr, size);

	if (new_ptr) {
		*ptr = new_ptr;
		printf("Re-allocated from %zu to %zu bytes\n", current_size, size);
		return 1;

	} else {
		printf("Failed to re-allocate from %zu to %zu bytes\n", current_size, size);
		return 0;
	}
}

void mem_free(void* ptr, size_t size) {
	free(ptr);
	printf("Freed %zu bytes\n", size);
}