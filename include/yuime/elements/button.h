#pragma once

#include "../API.h"
#include "../base/event.h"
#include "../base/element.h"
#include "../base/geometry.h"
#include "../base/context.h"

typedef struct yuime_element_button_s {
	yuime_element* base;

	yuime_dim2 min_size;
	yuime_dim2 max_size;
	yuime_geometry geometry;
} yuime_element_button;

/**
 * @brief Initializes button element.
 * 
 * @param ctx 
 * @param button 
 * @param geometry 
 * @returns 0 if failed to add element to ctx->elements or if ctx or button is NULL.
 */
YUIME_API uint8_t yuime_element_button_init(yuime_context* ctx, yuime_element_button* button, yuime_geometry geometry, yuime_element_flag_t element_flags);