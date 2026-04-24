#pragma once

#include <stdint.h>

/// Built-in widget types.
typedef uint16_t yuime_widget_type_t;
enum yuime_widget_type_e {
	YUIME_WIDGET_TYPE_NONE = 0,
	YUIME_WIDGET_TYPE_PANEL,
	YUIME_WIDGET_TYPE_COUNT, ///< Use it for unknown/null widgets.
};