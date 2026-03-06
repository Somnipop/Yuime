#pragma once

#include "vector2.h"

typedef struct yuime_dim2_s {
	yuime_vector2 scale; ///< Relative (percentage).
	yuime_vector2 offset; ///< Absolute (pixel).
} yuime_dim2;

#define YUIME_CALC_DIM2_SIZE(parent_size, scale, offset) (parent_size * scale + offset)
#define YUIME_CALC_DIM2_POSITION(parent_pos, parent_size, element_size, scale, offset, pivot) \
	(parent_pos + parent_size * scale + offset - element_size * pivot)