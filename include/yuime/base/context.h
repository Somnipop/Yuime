#pragma once

#include <stdint.h>

#include "alloc.h"
#include "element_array.h"
#include "element.h"
#include "render.h"
#include "resize_region.h"


typedef uint8_t yuime_context_flag_t;
typedef enum yuime_context_flag_e {
	YUIME_CONTEXT_FLAG_NONE = 0,
	YUIME_CONTEXT_FLAG_DRAGGING = 1,
	YUIME_CONTEXT_FLAG_RESIZING = 2,
	YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY = 4,
	YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY = 8,
	YUIME_CONTEXT_FLAG_DRAW_CURSOR = 16
} yuime_context_flag;

#define YUIME_CONTEXT_FLAG_SCROLLING_ANY(flags) ((flags & YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY) | (flag & YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY))
#define YUIME_CONTEXT_FLAG_SCROLLING_ALL(flags) ((flags & YUIME_CONTEXT_FLAG_SCROLLING_VERTICALLY) & (flag & YUIME_CONTEXT_FLAG_SCROLLING_HORIZONTALLY))


typedef struct yuime_context_s {
	yuime_memory_functions memory;
	yuime_render_callback render;

	yuime_element_array elements;

	yuime_element *focused_element;
	yuime_element *hovered_element;
	yuime_element *pressed_element;

	yuime_resize_region_t resize_region;
	yuime_resize_region_t hovered_resize_region;

	yuime_context_flag_t flags;
} yuime_context;

/**
 * @brief Sets default values for the given context.
 * @param ctx Context to initialize.
 * @param mem_functions memory functions related to memory allocation and deallocation.
 */
YUIME_API void yuime_context_init(yuime_context *ctx, yuime_memory_functions mem_functions, yuime_render_callback render);

YUIME_API void yuime_context_cleanup(yuime_context *ctx);

/**
 * @brief Adds an element to ctx->elements
 * @param ctx Context to add element to.
 * @param element Memory address of the element to be copied and added.
 * @returns NULL if failed.
 */
YUIME_API yuime_element *yuime_context_element_add(yuime_context *ctx, const yuime_element *element);