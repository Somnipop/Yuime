#include "yuime/elements/button.h"

#include "yuime/base/dimension2.h"
#include "yuime/elements/type.h"

#include <string.h>

uint8_t yuime_element_button_init(yuime_context* ctx, yuime_element_button* button, yuime_geometry geometry, yuime_element_flag_t element_flags) {
	if (ctx == NULL || button == NULL) {
		return 0;
	}

	memset(button, 0, sizeof(yuime_element_button));

	button->geometry = geometry;

	button->min_size = (yuime_dim2){
		.scale = {0.0f, 0.0f},
		.offset = {1.0f, 1.0f}
	};

	button->max_size = (yuime_dim2){
		.scale = {1.0f, 1.0f},
		.offset = {0.0f, 0.0f}
	};

	yuime_element element;
	yuime_element_init(&element, NULL, (yuime_element_object){
		.type = YUIME_ELEMENT_TYPE_BUTTON,
		.obj = &button
	}, YUIME_ELEMENT_FLAG_NONE);

	button->base = yuime_context_element_add(ctx, &element);
	

	// TODO: call on window resize

	if (button->base == NULL)
		return 0;

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