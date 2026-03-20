#include "mem_alloc.h"

#include <stdlib.h>

#ifndef NDEBUG
#include <stdio.h>

static size_t allocations = 0;
static size_t allocations_in_bytes = 0;

static size_t reallocations_total = 0;
static size_t reallocations_total_in_bytes = 0;

static size_t allocations_total = 0;
static size_t allocations_total_in_bytes = 0;
#endif // !NDEBUG


uint8_t mem_alloc(void** ptr, size_t size) {
	*ptr = malloc(size);

	if (*ptr) {
#ifndef NDEBUG
		printf("Allocated %zu bytes\n", size);
		allocations++;
		allocations_in_bytes += size;

		allocations_total++;
		allocations_total_in_bytes += size;
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
#ifndef NDEBUG
		if (current_size == 0 || *ptr == NULL) {
			printf("Allocated calling mem_realloc(), from %zu to %zu bytes\n", current_size, size);
			allocations++;
			allocations_total++;
		} else {
			printf("Re-allocated from %zu to %zu bytes\n", current_size, size);
			reallocations_total++;
		}

		allocations_in_bytes -= current_size;
		allocations_in_bytes += size;

		allocations_total_in_bytes -= current_size;
		allocations_total_in_bytes += size;

		reallocations_total_in_bytes -= current_size;
		reallocations_total_in_bytes += size;
#endif // !NDEBUG
		*ptr = new_ptr;
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
	allocations--;
	allocations_in_bytes -= size;
#endif // !NDEBUG
}

#ifndef NDEBUG
void mem_print_stats() {
	printf("--- HEAP STATUS ---\nAllocations total: %zu (%zu bytes)\nReallocations total: %zu (%zu bytes)\nCurrently allocated: %zu (%zu bytes)\n-------------------\n",
		allocations_total, allocations_total_in_bytes,
		reallocations_total, reallocations_total_in_bytes,
		allocations, allocations_in_bytes
	);
}
#endif // !NDEBUG