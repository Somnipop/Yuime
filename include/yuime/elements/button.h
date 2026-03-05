#pragma once

#include "../API.h"

#include "../vector2.h"
#include "../geometry.h"

typedef struct {
	yuime_vector2 minSize;
	yuime_vector2 maxSize;

	yuime_geometry geometry;
} yuime_element_button;