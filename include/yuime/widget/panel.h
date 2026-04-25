#pragma once

#include "../API.h"

#include "../alloc.h"

#include "../math/rect.h"
#include "../math/dimension2.h"
#include "../math/geometry.h"

#include "../style/color.h"
#include "../style/border.h"

#include "../node.h"
#include "../context.h"

#include "widget.h"

typedef struct yuime_widget_panel_style_s {
	yuime_style_border_t border;
} yuime_widget_panel_style_t;

typedef struct yuime_widget_panel_s {
	yuime_widget_panel_style_t* style;

	yuime_dim2_t min_size;
	yuime_dim2_t max_size;

	yuime_geometry_t geometry;

	yuime_rect_t rect;
} yuime_widget_panel_t;

#define YUIME_WIDGET_PANEL(ctx_ptr, var, parent_ptr_or_null, _geometry) \
	{ \
		yuime_geometry_t __geometry = _geometry; \
		var = yuime_widget_panel_new_node(ctx_ptr, parent_ptr_or_null, &__geometry); \
	}

/**
 * @brief Creates a new widget.
 * 
 * @param mem_alloc Memory allocation function. 
 * @returns widget.
 */
inline yuime_widget_panel_t *yuime_widget_panel_new(yuime_mem_alloc_t mem_alloc) {
	yuime_widget_panel_t *widget = (yuime_widget_panel_t*)yuime_widget_new(mem_alloc, sizeof(yuime_widget_panel_t));
	if (widget == NULL) {
		return NULL;
	}

	return widget;
}

/**
 * @brief Creates a new node with widget inserted into it.
 * 
 * @param ctx
 * @param parent can be NULL.
 * @param geometry If not NULL, sets node and widget geometry and defaults on_window_resize, on_resize and on_move. Can be NULL.
 * @returns node.
 */
YUIME_API yuime_node_t *yuime_widget_panel_new_node(yuime_context_t *ctx, yuime_node_t *parent, const yuime_geometry_t *geometry);