#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

#include "init.h"

enum {
	ELEMENT_TYPE_NONE = 0,
	ELEMENT_TYPE_BUTTON,
	ELEMENT_TYPE_COUNT
};

void render_element_rect(SDL_Renderer* renderer, yuime_element* element) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderRect(renderer, (SDL_FRect*)&element->rect);
}

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	yuime_context ctx;

	init(&ctx, &window, &renderer);

	yuime_dim2 size = {
		.scale = {0.5f, 0.5f},
		.offset = {0.0f, 0.0f}
	};

	yuime_element_button btn;
	yuime_element_button_init(&ctx, ELEMENT_TYPE_BUTTON, &btn, (yuime_geometry){
					.pivot = {0.5f, 0.5f},
					.position = {
						.scale = {0.5f, 0.5f},
						.offset = {0.0f, 0.0f}
					},
					.size = &size
			});

	SDL_Event event;
	uint8_t running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			yuime_context_send_event(&ctx, &event);
			if (event.type == SDL_EVENT_QUIT) {
				running = 0;
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);

		render_element_rect(renderer, btn.base);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	return 0;
}