#pragma once

#include <string.h>

#include "../alloc.h"

#include <stdint.h>

/// Built-in widget types.
typedef uint16_t yuime_widget_type_t;
enum yuime_widget_type_e {
	YUIME_WIDGET_TYPE_NONE = 0,
	YUIME_WIDGET_TYPE_PANEL,
	YUIME_WIDGET_TYPE_COUNT, ///< Use it for unknown/null widgets.
};

typedef struct yuime_widget_s {
	yuime_widget_type_t type;
	uint16_t size;
	void *widget;
} yuime_widget_t;


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