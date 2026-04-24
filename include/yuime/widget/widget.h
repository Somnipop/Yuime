#pragma once

#include <string.h>

#include "../context.h"

inline void *yuime_widget_new(yuime_mem_alloc_t mem_alloc, size_t size) {
	void* widget = NULL;
	mem_alloc(YUIME_ALLOC_CONTEXT_WIDGET, &widget, size);

	if (widget != NULL) {
		memset(widget, 0, size);
	}

	return widget;
}

inline void yuime_widget_free(yuime_mem_free_t mem_free, void *widget, size_t size) {
	if (widget != NULL) {
		mem_free(YUIME_ALLOC_CONTEXT_WIDGET, widget, size);
	}

}