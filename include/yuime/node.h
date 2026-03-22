#pragma once

#include <stdint.h>

#include "API.h"

#include "math/rect.h"
#include "math/geometry.h"

typedef struct yuime_node_s {
	yuime_dim2_t min_size;
	yuime_dim2_t max_size;
	yuime_geometry_t geometry;
	yuime_rect_t rect;

	struct yuime_node_s *parent;
	struct yuime_node_s* first_child;
	struct yuime_nide_s* next;
} yuime_node_t;