#pragma once

#include "../API.h"

#define YUIME_ELEMENT_TYPES(X) \
	X(YUIME_ELEMENT_TYPE_NONE, "undefined") \
	X(YUIME_ELEMENT_TYPE_RECTANGLE, "rectangle") \
	X(YUIME_ELEMENT_TYPE_BUTTON, "button") \
	X(YUIME_ELEMENT_TYPE_WINDOW, "window") \
	X(YUIME_ELEMENT_TYPE_COUNT, "undefined")

#define _YUIME_XMACRO_VAR(var, str) var,
typedef enum yuime_element_type_e {
	YUIME_ELEMENT_TYPES(_YUIME_XMACRO_VAR)
} yuime_element_type;
#undef _YUIME_XMACRO_VAR

YUIME_API const char *yuime_element_type_name(yuime_element_type type);