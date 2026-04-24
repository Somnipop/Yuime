#include "sdl.h"

#include <SDL3/SDL.h>

#include <yuime/widget/panel.h>

yuime_children_iterate_return_signal_t sdl_render_node(yuime_context_t *ctx, yuime_node_t *node, void* data) {
	if (node->rect == NULL /*|| !node->is_visible*/) {
		return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_NO_CHILDREN;
	}

	SDL_Renderer* renderer = (SDL_Renderer*)ctx->data;

	// if (node->draw != NULL) {
	// 	node->draw(ctx, node, data);
	// }

	SDL_FRect rect = (SDL_FRect){
		node->rect->x,
		node->rect->y,
		node->rect->w,
		node->rect->h
	};

	// draw border
	if (node->widget != NULL && node->widget_type == YUIME_WIDGET_TYPE_PANEL) {
		yuime_widget_panel_t *panel = (yuime_widget_panel_t*)node->widget;
		SDL_SetRenderDrawColor(renderer, panel->style->border.color.r, panel->style->border.color.g, panel->style->border.color.b, panel->style->border.color.a);
	}
	SDL_RenderFillRect(renderer, &rect);

	// draw rect
	// rect = (SDL_FRect){
	// 	node->rect.x+node->style->border.size,
	// 	node->rect.y+node->style->border.size,
	// 	node->rect.w-node->style->border.size*2,
	// 	node->rect.h-node->style->border.size*2
	// };

	// SDL_SetRenderDrawColor(renderer, node->style->color.r, node->style->color.g, node->style->color.b, node->style->color.a);
	// SDL_RenderFillRect(renderer, &rect);
	return YUIME_CHILDREN_ITERATE_RETURN_SIGNAL_PASS;
}