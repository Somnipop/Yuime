#include "yuime/elements/button.h"

#include "yuime/base/math/dimension2.h"
#include "yuime/elements/type.h"

#include <string.h>

uint8_t yuime_element_button_init(yuime_context_t *ctx, yuime_element_button_t *button, yuime_geometry_t geometry, yuime_element_event_callback_t event_callback, yuime_element_flag_t element_flags) {
	if (ctx == NULL || button == NULL) {
		return 0;
	}

	memset(button, 0, sizeof(yuime_element_button_t));

	button->geometry = geometry;

	button->min_size = (yuime_dim2_t){
		.scale = {0.0f, 0.0f},
		.offset = {1.0f, 1.0f}
	};

	button->max_size = (yuime_dim2_t){
		.scale = {1.0f, 1.0f},
		.offset = {0.0f, 0.0f}
	};

	yuime_element_init(&button->base, event_callback, (yuime_element_object){
		.type = YUIME_ELEMENT_TYPE_BUTTON,
		.obj = button
	}, element_flags);

	if (!yuime_context_element_add(ctx, &button->base)) {
		return 0;
	}

	if (button->base.event_callback) {
		button->base.event_callback(ctx, &button->base, YUIME_EVENT_RESIZE, NULL);
	}
	// TODO: call on window resize

	return 1;
}

/*
function Button.new(layout, onPress, onRelease)
    local self = setmetatable({}, Button)
    self.rect = SDL.FRect.new(0,0,0,0)

	self.layout = layout
	if self.layout then
		self.onWindowResize = Sudado.defaultOnWindowResize
		self.onResize = Sudado.defaultOnResize
		self.onMove = Sudado.defaultOnMove
		self:onWindowResize(SDL.FPoint.new(1,1), SDL.Point.new(1,1))
	end

	self.backgroundColor = SDL.Color.new(50,50,50,255)
	self.pressedColor = SDL.Color.new(20,20,20,255)
	self.hoveredColor = SDL.Color.new(35,35,35,255)

	self.onPress = onPress
	self.onRelease = onRelease

    return self
end
*/