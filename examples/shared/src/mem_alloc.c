#include "mem_alloc.h"

#include <stdlib.h>

#ifndef NDEBUG
#include <stdio.h>

static size_t allocations = 0;
static size_t allocations_in_bytes = 0;

static size_t allocations_total = 0;
static size_t allocations_total_in_bytes = 0;


static size_t reallocations_total = 0;

typedef struct mem_alloc_contextualized_s {
	size_t allocations;
	size_t allocations_in_bytes;

	size_t allocations_total;
	size_t allocations_total_in_bytes;

	size_t reallocations_total;
} mem_alloc_contextualized_t;

static mem_alloc_contextualized_t allocations_contextualized[YUIME_ALLOC_CONTEXT_COUNT] = {0};
#endif // !NDEBUG


uint8_t mem_alloc(yuime_alloc_context_t ctx, void** ptr, size_t size) {
#ifdef NDEBUG
	(void)ctx;
#endif

	*ptr = malloc(size);

	if (*ptr) {
#ifndef NDEBUG
		printf("Allocated %zu bytes\n", size);
		allocations++;
		allocations_in_bytes += size;

		allocations_total++;
		allocations_total_in_bytes += size;

		if (ctx < YUIME_ALLOC_CONTEXT_COUNT) {
			allocations_contextualized[ctx].allocations++;
			allocations_contextualized[ctx].allocations_total++;

			allocations_contextualized[ctx].allocations_in_bytes += size;
			allocations_contextualized[ctx].allocations_total_in_bytes += size;
		}
#endif // !NDEBUG
		return 1;

	} else {
#ifndef NDEBUG
		printf("Failed to allocate %zu bytes\n", size);
#endif // !NDEBUG
		return 0;
	}
}

uint8_t mem_realloc(yuime_alloc_context_t ctx, void** ptr, size_t current_size, size_t new_size) {
#ifdef NDEBUG
	(void)ctx;
#endif

	if (current_size == 0 || *ptr == NULL) {
#ifndef NDEBUG
		printf("mem_realloc() is calling mem_alloc()\n");
#endif
		return mem_alloc(ctx, ptr, new_size);
	}

	void* new_ptr = realloc(*ptr, new_size);

	if (new_ptr) {
#ifndef NDEBUG
		printf("Re-allocated from %zu to %zu bytes\n", current_size, new_size);
		reallocations_total++;

		allocations_in_bytes += new_size;
		allocations_in_bytes -= current_size;

		allocations_total_in_bytes += new_size;
		allocations_total_in_bytes -= current_size;

		if (ctx < YUIME_ALLOC_CONTEXT_COUNT) {
			allocations_contextualized[ctx].reallocations_total++;

			allocations_contextualized[ctx].allocations_in_bytes += new_size;
			allocations_contextualized[ctx].allocations_in_bytes -= current_size;

			allocations_contextualized[ctx].allocations_total_in_bytes += new_size;
			allocations_contextualized[ctx].allocations_total_in_bytes -= current_size;
		}
#endif // !NDEBUG
		*ptr = new_ptr;
		return 1;

	} else {
#ifndef NDEBUG
		printf("Failed to re-allocate from %zu to %zu bytes\n", current_size, new_size);
#endif // !NDEBUG
		return 0;
	}
}

void mem_free(yuime_alloc_context_t ctx, void* ptr, size_t size) {
#ifdef NDEBUG
	(void)ctx;
	(void)size;
#endif

	free(ptr);
#ifndef NDEBUG
	printf("Freed %zu bytes\n", size);
	allocations--;
	allocations_in_bytes -= size;

	if (ctx < YUIME_ALLOC_CONTEXT_COUNT) {
		allocations_contextualized[ctx].allocations--;
		allocations_contextualized[ctx].allocations_in_bytes -= size;
	}
#endif // !NDEBUG
}

#ifndef NDEBUG
void mem_print_stats() {
	printf("------ HEAP STATUS ------\nAllocations total: %zu (%zu bytes)\n", allocations_total, allocations_total_in_bytes);

#define X(var, id, name) \
	printf( \
		" - " name ": %zu (%zu bytes)\n", \
		allocations_contextualized[id].allocations, \
		allocations_contextualized[id].allocations_in_bytes \
	);

	_YUIME_ALLOC_CONTEXT_LIST(X)
#undef X

	printf("Reallocations total: %zu\n", reallocations_total);

#define X(var, id, name) \
	printf( \
		" - " name ": %zu\n", \
		allocations_contextualized[id].reallocations_total \
	);

	_YUIME_ALLOC_CONTEXT_LIST(X)
#undef X

	printf("Currently allocated: %zu (%zu bytes)\n", allocations, allocations_in_bytes);

#define X(var, id, name) \
	printf( \
		" - " name ": %zu (%zu bytes)\n", \
		allocations_contextualized[id].allocations_total, \
		allocations_contextualized[id].allocations_total_in_bytes \
	);

	_YUIME_ALLOC_CONTEXT_LIST(X)
#undef X

	printf("-------------------------\n");

	// printf("--- HEAP STATUS ---\nAllocations total: %zu (%zu bytes)\n - Nodes: %zu (%zu bytes)\n - Widgets: %zu (%zu bytes)\nReallocations total: %zu\n - Nodes: %zu\n - Widgets: %zu\nCurrently allocated: %zu (%zu bytes)\n - Nodes: %zu (%zu bytes)\n - Widgets: %zu (%zu bytes)\n-------------------\n",
	// 	allocations_total, allocations_total_in_bytes,
	// 	allocations_nodes_total, allocations_nodes_total_in_bytes,
	// 	allocations_widgets_total, allocations_widgets_total_in_bytes,
	// 	reallocations_total,
	// 	reallocations_nodes_total,
	// 	reallocations_widgets_total,
	// 	allocations, allocations_in_bytes,
	// 	allocations_nodes, allocations_nodes_in_bytes,
	// 	allocations_widgets, allocations_widgets_in_bytes
	// );
}
#endif // !NDEBUG