#include "yuime/widget/events.h"

#include "yuime/math/rect.h"
#include "yuime/math/dimension2.h"
#include "yuime/math/geometry.h"

void yuime_widget_on_window_resize(yuime_context_t *ctx, yuime_node_t *node, yuime_vector2_t ratio, yuime_vector2_t delta) {
	if (node->rect == NULL) {
		return;
	}

	yuime_rect_t parent_rect = node->parent == NULL?
								(yuime_rect_t){0.0f, 0.0f, ctx->screen_size.x, ctx->screen_size.y}
								: *node->parent->rect;

	yuime_geometry_calculate_rect(node->geometry, &parent_rect, node->rect);

	if (node->min_size != NULL) {
		yuime_vector2_t min_size = (yuime_vector2_t){
			yuime_dim2_calculate_size(parent_rect.w, node->min_size->scale.x, node->min_size->offset.x),
			yuime_dim2_calculate_size(parent_rect.h, node->min_size->scale.y, node->min_size->offset.y)
		};

		if (node->rect->w < min_size.x) {
			node->rect->w = min_size.x;
		}

		if (node->rect->h < min_size.y) {
			node->rect->h = min_size.y;
		}
	}

	if (node->max_size != NULL) {
		yuime_vector2_t max_size = (yuime_vector2_t){
			yuime_dim2_calculate_size(parent_rect.w, node->max_size->scale.x, node->max_size->offset.x),
			yuime_dim2_calculate_size(parent_rect.h, node->max_size->scale.y, node->max_size->offset.y),
		};

		if (max_size.x != 0.0f && node->rect->w > max_size.x) {
			node->rect->w = max_size.x;
		}

		if (max_size.y != 0.0f && node->rect->h > max_size.y) {
			node->rect->h = max_size.y;
		}
	}
}

void yuime_widget_on_resize(yuime_context_t *ctx, yuime_node_t *node) {
	return;
}

void yuime_widget_on_move(yuime_context_t *ctx, yuime_node_t *node) {
	return;
}