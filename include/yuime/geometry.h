#pragma once

#include "API.h"

#include "vector2.h"
#include "dimension2.h"

typedef struct {
	yuime_vector2 pivot; ///< origin of the geometry
	yuime_dim2 position;
	yuime_dim2 size;
} yuime_geometry;