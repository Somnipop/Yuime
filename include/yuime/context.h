#pragma once

#include <stdint.h>

#include "alloc.h"

#include "math/vector2.h"

#include "node.h"

#include "resize_region.h"


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
	yuime_mem_functions_t memory;

	yuime_vector2_t screen_size;

	yuime_node_t *node_tree;

	yuime_node_t *focused_node;
	yuime_node_t *hovered_node;
	yuime_node_t *pressed_node;

	yuime_resize_region_t resize_region;
	yuime_resize_region_t hovered_resize_region;

	yuime_context_flag_t flags;
} yuime_context_t;

/**
 * @brief Sets default values for the given context.
 * @param ctx Context to initialize.
 * @param mem_functions memory functions related to memory allocation and deallocation.
 */
YUIME_API void yuime_context_init(yuime_context_t *ctx, const yuime_vector2_t screen_size, yuime_mem_functions_t mem_functions);
YUIME_API void yuime_context_cleanup(yuime_context_t *ctx);