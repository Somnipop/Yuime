#include "yuime/events.h"

#include "yuime/math/vector2.h"

static inline yuime_children_iterate_return_signal_t _yuime_node_iterate_window_resize_event(yuime_context_t *ctx, yuime_node_t *node, void* _data) {
	if (node->on_window_resize != NULL) {
		yuime_vector2_t *data = (yuime_vector2_t*)_data;
		node->on_window_resize(ctx, node, data[0], data[1]);
	}
	return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS;
}

void yuime_event_window_resize(yuime_context_t *ctx, yuime_vector2_t screen_size) {
	ctx->screen_size.x = screen_size.x;
	ctx->screen_size.y = screen_size.y;

	if (ctx->node_tree == NULL) {
		return;
	}

	yuime_vector2_t data[2] = {0};
	{
		yuime_vector2_t ratio = (yuime_vector2_t){1.0f, 1.0f};

		if (ctx->screen_size.x != 0.0f) {
			ratio.x = screen_size.x/ctx->screen_size.x;
		}

		if (ctx->screen_size.y != 0.0f) {
			ratio.y = screen_size.y/ctx->screen_size.y;
		}

		yuime_vector2_t delta = (yuime_vector2_t){
			screen_size.x-ctx->screen_size.x,
			screen_size.y-ctx->screen_size.y
		};

		data[0] = ratio;
		data[1] = delta;
	}

	yuime_node_t *node = ctx->node_tree;

	while (node != NULL) {
		if (node->on_window_resize != NULL) {
			node->on_window_resize(ctx, node, data[0], data[1]);
		}

		yuime_node_iterate_children(ctx, node, _yuime_node_iterate_window_resize_event, data);
		node = node->next;
	}
}


static inline yuime_children_iterate_return_signal_t _yuime_node_iterate_resize_event(yuime_context_t *ctx, yuime_node_t *node, void* data) {
	(void)data;

	if (node->on_resize != NULL) {
		node->on_resize(ctx, node);
	}
	return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS;
}

void yuime_event_resize(yuime_context_t *ctx, yuime_node_t *node) {
	if (node->on_resize != NULL) {
		node->on_resize(ctx, node);
	}
	yuime_node_iterate_children(ctx, node, _yuime_node_iterate_resize_event, NULL);
}