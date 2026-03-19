#pragma once

#include "../API.h"

#define YUIME_ELEMENT_TYPES(X) \
	X(YUIME_ELEMENT_TYPE_NONE, 0, "undefined") \
	X(YUIME_ELEMENT_TYPE_RECTANGLE, 1, "rectangle") \
	X(YUIME_ELEMENT_TYPE_BUTTON, 2, "button") \
	X(YUIME_ELEMENT_TYPE_WINDOW, 3, "window") \

#define _YUIME_XMACRO_VAR(var, value, str) var = value,
typedef enum yuime_element_type_e {
	YUIME_ELEMENT_TYPES(_YUIME_XMACRO_VAR)
} yuime_element_type;
#undef _YUIME_XMACRO_VAR

YUIME_API const char* yuime_element_type_name(yuime_element_type type);