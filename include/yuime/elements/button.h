#pragma once

#include "../API.h"
#include "../base/event.h"
#include "../base/element/element.h"
#include "../base/math/geometry.h"
#include "../base/context.h"

typedef struct yuime_element_button_s {
	yuime_element_t base;

	yuime_dim2_t min_size;
	yuime_dim2_t max_size;
	yuime_geometry_t geometry;
} yuime_element_button_t;

/**
 * @brief Initializes button element.
 * 
 * @param ctx 
 * @param button 
 * @param geometry 
 * @returns 0 if failed to add element to ctx->elements or if ctx or button is NULL.
 */
YUIME_API uint8_t yuime_element_button_init(yuime_context_t *ctx, yuime_element_button_t *button, yuime_geometry_t geometry, yuime_element_event_callback_t event_callback, yuime_element_flag_t element_flags);