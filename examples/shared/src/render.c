#include "render.h"

#include <SDL3/SDL.h>

void render_element(yuime_context* ctx, yuime_element* element, void* data) {
	SDL_SetRenderDrawColor((SDL_Renderer*)data, 255, 0, 0, 255);
	SDL_RenderFillRect((SDL_Renderer*)data, (SDL_FRect*)&element->rect);
}