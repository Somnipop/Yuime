#include "yuime/elements/type.h"

const char* yuime_element_type_name(yuime_element_type type) {
#define _YUIME_XMACRO_SWITCH(var, value, str) case var: return str;
	switch (type) {
		YUIME_ELEMENT_TYPES(_YUIME_XMACRO_SWITCH)
		default: return "unknown";
	}
#undef _YUIME_XMACRO_SWITCH
}