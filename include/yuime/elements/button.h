#ifdef YUIME_BUILD_ELEMENTS
#pragma once

#include "../API.h"
#include "../event.h"
#include "../element.h"
#include "../geometry.h"
#include "../context.h"

typedef struct yuime_element_button_s {
	yuime_element* base;

	yuime_dim2 min_size;
	yuime_dim2 max_size;
	yuime_geometry geometry;
} yuime_element_button;
#endif

/**
 * @brief 
 * 
 * @param ctx 
 * @param element_type 
 * @param button 
 * @param geometry 
 * @returns 0 if failed to add element to ctx->elements or if ctx or button is NULL.
 */
YUIME_API uint8_t yuime_element_button_init(yuime_context* ctx, uint32_t element_type, yuime_element_button* button, yuime_geometry geometry);