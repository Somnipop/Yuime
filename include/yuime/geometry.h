#pragma once

#include "API.h"

#include "vector2.h"
#include "dimension2.h"

/**
 * @brief Rectangle geometry.
 */
typedef struct yuime_geometry_s {
	yuime_vector2 pivot; ///< Origin of the geometry.
	yuime_dim2 position;
	yuime_dim2* size; ///< Pointer to size. Why? Because size could be shared with other geometries.
} yuime_geometry;