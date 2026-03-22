#include "render.h"

#include <SDL3/SDL.h>

void render_element(yuime_context_t* ctx, yuime_element_t* element, void* data) {
	SDL_SetRenderDrawColor((SDL_Renderer*)data, 255, 0, 0, 255);
	SDL_RenderFillRect((SDL_Renderer*)data, (SDL_FRect*)&element->rect);
}