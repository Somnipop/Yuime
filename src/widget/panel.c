#include "yuime/widget/panel.h"

#include "yuime/context.h"

#include "yuime/widget/events.h"
#include "yuime/widget/type.h"
#include "yuime/widget/widget.h"

yuime_node_t *yuime_widget_panel_new_node(yuime_context_t *ctx, yuime_node_t *parent, const yuime_geometry_t *geometry) {
	yuime_node_t *node = yuime_node_new(ctx, parent);
	if (node == NULL) {
		return NULL;
	}

	yuime_widget_panel_t *panel = (yuime_widget_panel_t*)yuime_widget_panel_new(ctx->memory.alloc);
	if (panel == NULL) {
		yuime_node_free(ctx, node);
		return NULL;
	}
	node->widget_size = sizeof(yuime_widget_panel_t);

	node->rect = &panel->rect;

	if (geometry != NULL) {
		panel->geometry = *geometry;
		node->geometry = &panel->geometry;

		node->on_window_resize = yuime_widget_on_window_resize;
		node->on_resize = yuime_widget_on_resize;
		node->on_move = yuime_widget_on_move;
		node->on_window_resize(ctx, node, (yuime_vector2_t){1,1}, (yuime_vector2_t){0,0});
	}

	node->widget_type = YUIME_WIDGET_TYPE_PANEL;
	node->widget = panel;

	return node;
}

void yuime_widget_panel_draw(yuime_context_t *ctx, void* widget) {
	/*
	SDL.Render.setRenderDrawColorEx(renderer, self.backgroundColor.r, self.backgroundColor.g, self.backgroundColor.b, self.backgroundColor.a)
    SDL.Render.renderFillRect(renderer, self.rect)

	-- Borders
	SDL.Render.setRenderDrawColorEx(renderer, self.borderColor.r, self.borderColor.g, self.borderColor.b, self.borderColor.a)

	-- Left
	local borderRect = SDL.FRect.new(self.rect.x, self.rect.y, self.bordersSizes.x, self.rect.h)
	SDL.Render.renderFillRect(renderer, borderRect)

	-- Top
	borderRect.w = self.rect.w
	borderRect.h = self.bordersSizes.y
	SDL.Render.renderFillRect(renderer, borderRect)

	-- Right
	borderRect.x = self.rect.x+self.rect.w-self.bordersSizes.w
	borderRect.w = self.bordersSizes.w
	borderRect.h = self.rect.h
	SDL.Render.renderFillRect(renderer, borderRect)

	-- Bottom
	borderRect.x = self.rect.x
	borderRect.y = self.rect.y+self.rect.h-self.bordersSizes.h
	borderRect.w = self.rect.w
	borderRect.h = self.bordersSizes.h
	SDL.Render.renderFillRect(renderer, borderRect)
	*/
}