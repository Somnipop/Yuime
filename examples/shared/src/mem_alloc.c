#include "mem_alloc.h"

#include <stdlib.h>

#ifndef NDEBUG
#include <stdio.h>

static size_t allocations = 0;
static size_t allocations_in_bytes = 0;

static size_t allocations_nodes = 0;
static size_t allocations_widgets = 0;

static size_t reallocations_total = 0;
static size_t reallocations_total_in_bytes = 0;

static size_t allocations_total = 0;
static size_t allocations_total_in_bytes = 0;

static size_t allocations_nodes_total = 0;
static size_t allocations_widgets_total = 0;
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

		switch (ctx) {
		case YUIME_ALLOC_CONTEXT_NODE:
			allocations_nodes++;
			allocations_nodes_total++;
			break;

		case YUIME_ALLOC_CONTEXT_WIDGET:
			allocations_widgets++;
			allocations_widgets_total++;
			break;

		default:
			break;
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

uint8_t mem_realloc(yuime_alloc_context_t ctx, void** ptr, size_t current_size, size_t size) {
#ifdef NDEBUG
	(void)ctx;
#endif

	void* new_ptr = realloc(*ptr, size);

	if (new_ptr) {
#ifndef NDEBUG
		if (current_size == 0 || *ptr == NULL) {
			printf("Allocated calling mem_realloc(), from %zu to %zu bytes\n", current_size, size);
			allocations++;
			allocations_total++;

			switch (ctx) {
			case YUIME_ALLOC_CONTEXT_NODE:
				allocations_nodes++;
				allocations_nodes_total++;
				break;

			case YUIME_ALLOC_CONTEXT_WIDGET:
				allocations_widgets++;
				allocations_widgets_total++;
				break;

			default:
				break;
			}
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

	switch (ctx) {
	case YUIME_ALLOC_CONTEXT_NODE:
		allocations_nodes--;
		break;

	case YUIME_ALLOC_CONTEXT_WIDGET:
		allocations_widgets--;	
		break;
	}
#endif // !NDEBUG
}

#ifndef NDEBUG
void mem_print_stats() {
	printf("--- HEAP STATUS ---\nAllocations total: %zu (%zu bytes)\n - Nodes: %zu\n - Widgets: %zu\nReallocations total: %zu (%zu bytes)\nCurrently allocated: %zu (%zu bytes)\n - Nodes: %zu\n - Widgets: %zu\n-------------------\n",
		allocations_total, allocations_total_in_bytes,
		allocations_nodes_total, allocations_widgets_total,
		reallocations_total, reallocations_total_in_bytes,
		allocations, allocations_in_bytes,
		allocations_nodes, allocations_widgets
	);
}
#endif // !NDEBUG