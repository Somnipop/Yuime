#include "event_handler.h"

#include <yuime/yuime.h>

static void _element_send_resize_event(const yuime_memory_functions_t *mem_funcs, yuime_element_pointer_array_t *children, yuime_element_pointer_array_index_t index, void *data) {
	if (children->data[index]->event_callback) {
		children->data[index]->event_callback((yuime_context_t*)data, children->data[index], YUIME_EVENT_RESIZE, NULL);
	}
}

uint8_t element_event_callback(yuime_context_t* ctx, yuime_element_t* element, uint32_t event_type, void* data) {
	if (element->self.type != YUIME_ELEMENT_TYPE_BUTTON) {
		return 0;
	}

	if (event_type == YUIME_EVENT_SCREEN_RESIZE && element->parent == NULL) {
		yuime_element_button_t* btn = (yuime_element_button_t*)element->self.obj;

		yuime_rect_t screen_rect = {0.0f, 0.0f, ctx->screen_size.x, ctx->screen_size.y};
		yuime_geometry_calculate_rect(
			&btn->geometry,
			&screen_rect,
			&btn->base.rect
		);

		if (element->children.count != 0) {
			yuime_element_children_iterate(&ctx->memory, &element->children, _element_send_resize_event, ctx);
		}
		return 1;
	}

	if (event_type == YUIME_EVENT_RESIZE && element->parent != NULL) {
		yuime_element_button_t* btn = (yuime_element_button_t*)element->self.obj;
		yuime_geometry_calculate_rect(
			&btn->geometry,
			&btn->base.parent->rect,
			&btn->base.rect
		);
		return 1;
	}

	return 0;
}