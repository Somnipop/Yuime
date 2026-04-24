#pragma once

#define YUIME_WIDGET(ctx_ptr, var_name, parent_ptr, widget_func, pivot_x, pivot_y, position_scale_x, position_offset_x, position_scale_y, position_offset_y, size_ptr) \
	yuime_node_t *var_name = NULL; \
	{ \
		yuime_geometry_t geometry = (yuime_geometry_t){ \
			.pivot = (yuime_vector2_t){ \
				.x = pivot_x, \
				.y = pivot_y \
			}, \
			.position = (yuime_dim2_t){ \
				.scale = (yuime_vector2_t){ \
					.x = position_scale_x, \
					.y = position_scale_y \
				}, \
				.offset = (yuime_vector2_t){ \
					.x = position_offset_x, \
					.y = position_offset_y \
				} \
			}, \
			.size = size_ptr \
		}; \
		var_name = widget_func(ctx_ptr, parent_ptr, &geometry); \
	}