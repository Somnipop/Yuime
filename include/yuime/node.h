#pragma once

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
} yuime_node_t;

struct yuime_context_s;
/**
 * @brief Creates a new node and inserts it in parent.
 * 
 * @param ctx can not be null
 * @param parent if NULL, node is created in root.
 * @returns NULL if failed to allocate memory.
 */
YUIME_API yuime_node_t *yuime_node_new(struct yuime_context_s *ctx, struct yuime_node_s *parent);