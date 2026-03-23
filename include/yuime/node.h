#pragma once

#include <stdint.h>

#include "API.h"

#include "math/rect.h"
#include "math/dimension2.h"
#include "math/geometry.h"

typedef struct yuime_node_s {
	struct yuime_node_s *parent;
	struct yuime_node_s *first_child;
	struct yuime_node_s *next;

	yuime_dim2_t min_size;
	yuime_dim2_t max_size;

	yuime_geometry_t geometry;

	yuime_rect_t rect;

	uint8_t is_visible	: 1;
	uint8_t _reserved	: 7;
} yuime_node_t;

struct yuime_context_s;
/**
 * @brief Creates a new node and inserts it in parent.
 * 
 * @param ctx Can not be NULL.
 * @param parent If NULL, node is created in root.
 * @returns NULL if failed to allocate memory.
 */
YUIME_API yuime_node_t *yuime_node_new(struct yuime_context_s *ctx, struct yuime_node_s *parent);

/**
 * @brief Frees a node together with its children and updates siblings pointers.
 * @param ctx Can not be NULL.
 * @param node Can not be NULL.
 */
YUIME_API void yuime_node_free(struct yuime_context_s *ctx, struct yuime_node_s *node);

/**
 * @brief Updates rect members according to geometry, max_size and min_size members.
 */
YUIME_API void yuime_node_update_rect(struct yuime_context_s *ctx, struct yuime_node_s *node);

/**
 * @returns anything above 0 if should stop iterating.
 */
typedef uint8_t(*yuime_children_iterate_function_t)(struct yuime_context_s *ctx, struct yuime_node_s *node, void* data);
/**
 * @brief Calls iter_function for every node below.
 * 
 * @param ctx Context passed to iter_function. Can be NULL.
 * @param node Parent of the nodes that iter_function will be used.
 * @param iter_function The function to be called for them.
 * @param data Data passed to iter_function. Can be NULL.
 */
YUIME_API void yuime_node_iterate_children(struct yuime_context_s *ctx, struct yuime_node_s *node, yuime_children_iterate_function_t iter_function, void *data);