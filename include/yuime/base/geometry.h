#pragma once

#include "../API.h"

#include "vector2.h"
#include "dimension2.h"
#include "rect.h"

/**
 * @brief Rectangle geometry.
 */
typedef struct yuime_geometry_s {
	yuime_vector2 pivot; ///< Origin of the geometry.
	yuime_dim2 position;
	yuime_dim2* size; ///< Pointer to size. Why? Because size could be shared with other geometries.
} yuime_geometry;

inline void yuime_geometry_calculate_rect(const yuime_geometry* geometry, const yuime_rect *parent_rect, yuime_rect *rect) {
	rect->w = yuime_dim2_calculate_size(parent_rect->w, geometry->size->scale.x, geometry->size->offset.x);
	rect->h = yuime_dim2_calculate_size(parent_rect->h, geometry->size->scale.y, geometry->size->offset.y);

	rect->x = yuime_dim2_calculate_position(parent_rect->x, parent_rect->w, rect->w, geometry->position.scale.x, geometry->position.offset.x, geometry->pivot.x);
	rect->y = yuime_dim2_calculate_position(parent_rect->y, parent_rect->h, rect->h, geometry->position.scale.y, geometry->position.offset.y, geometry->pivot.y);
}