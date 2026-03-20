#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

#include "init.h"

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	yuime_context ctx;

	init(&ctx, &window, &renderer);

	yuime_dim2 size = {
		.scale = {0.5f, 0.5f},
		.offset = {0.0f, 0.0f}
	};

	// yuime_element_button btn;
	// yuime_element_button_init(&ctx, &btn, (yuime_geometry){
	// 				.pivot = {0.5f, 0.5f},
	// 				.position = {
	// 					.scale = {0.5f, 0.5f},
	// 					.offset = {0.0f, 0.0f}
	// 				},
	// 				.size = &size
	// 		}, YUIME_ELEMENT_FLAG_NONE);

	yuime_element_button btns[4];
	for (int i = 0; i < 4; ++i) {
		yuime_element_button_init(&ctx, &btns[i], (yuime_geometry){
						.pivot = {0.5f, 0.5f},
						.position = {
							.scale = {0.5f, 0.5f},
							.offset = {0.0f, 0.0f}
						},
						.size = &size
				}, YUIME_ELEMENT_FLAG_NONE);
		if (i > 0) {
			btns[i].base->parent = btns[i-1].base;

			if (btns[i].base->parent->children.data == NULL) {
				yuime_element_pointer_array_init(&ctx.memory, &btns[i].base->parent->children, 1);
			}
			yuime_element_pointer_array_push(&ctx.memory, &btns[i].base->parent->children, btns[i].base);
		}
	}

	// yuime_set_visibility(&ctx.memory, btns[3].base, 1);
	// yuime_set_visibility(&ctx.memory, btns[2].base, 1);
	// yuime_set_visibility(&ctx.memory, btns[1].base, 1);
	yuime_set_visibility(&ctx.memory, btns[0].base, 1);
	return;
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

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	return 0;
}