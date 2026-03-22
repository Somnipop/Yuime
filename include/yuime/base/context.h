#pragma once

#include <stdint.h>

#include "alloc.h"

#include "math/vector2.h"

#include "element/pointer_array.h"
#include "element/element.h"

#include "render.h"
#include "resize_region.h"

#include "event.h"


typedef uint8_t yuime_context_flag_t;
enum yuime_context_flag_e {
	YUIME_CONTEXT_FLAG_NONE = 0,
	YUIME_CONTEXT_FLAG_DRAGGING = 1,
	YUIME_CONTEXT_FLAG_RESIZING = 2,
	YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY = 4,
	YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY = 8,
	YUIME_CONTEXT_FLAG_DRAW_CURSOR = 16
};

#define YUIME_CONTEXT_FLAG_SCROLLING_ANY(flags) ((flags & YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY) | (flag & YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY))
#define YUIME_CONTEXT_FLAG_SCROLLING_ALL(flags) ((flags & YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY) & (flag & YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY))


typedef struct yuime_context_s {
	yuime_memory_functions_t memory;
	yuime_render_callback_t render;

	yuime_event_callback_t event_callback;

	yuime_vector2_t screen_size;

	yuime_element_pointer_array_t elements;

	yuime_element_t *focused_element;
	yuime_element_t *hovered_element;
	yuime_element_t *pressed_element;

	yuime_resize_region_t resize_region;
	yuime_resize_region_t hovered_resize_region;

	yuime_context_flag_t flags;
} yuime_context_t;

/**
 * @brief Sets default values for the given context.
 * @param ctx Context to initialize.
 * @param mem_functions memory functions related to memory allocation and deallocation.
 */
YUIME_API void yuime_context_init(yuime_context_t *ctx, const yuime_vector2_t screen_size, yuime_memory_functions_t mem_functions, yuime_render_callback_t render);
YUIME_API void yuime_context_cleanup(yuime_context_t *ctx);

/**
 * @brief Adds an element to ctx->elements.
 * @param ctx Context to add element to.
 * @param element Memory address of the element to be added to elements array.
 * @returns 0 if failed
 */
YUIME_API uint8_t yuime_context_element_add(yuime_context_t *ctx, yuime_element_t *element);