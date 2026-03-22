#pragma once

struct yuime_context_s;
struct yuime_element_s;
typedef void(*yuime_render_element_callback_t)(struct yuime_context_s *ctx, struct yuime_element_s *element, void *data);

typedef struct yuime_render_callback_s {
	yuime_render_element_callback_t element;
	void *data;
} yuime_render_callback_t;