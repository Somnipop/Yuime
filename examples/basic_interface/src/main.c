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

	yuime_element_button btn;
	yuime_element_button_init(&ctx, &btn, (yuime_geometry){
				.pivot = {0.5f, 0.5f},
				.position = {
					.scale = {0.5f, 0.5f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, YUIME_ELEMENT_FLAG_NONE
	);
	yuime_set_visibility(&ctx.memory, btn.base, 1);

	btn.base->rect.w = yuime_dim2_calculate_size(800.0f, btn.geometry.position.scale.x, btn.geometry.position.offset.x);
	btn.base->rect.h = yuime_dim2_calculate_size(600.0f, btn.geometry.position.scale.y, btn.geometry.position.offset.y);

	btn.base->rect.x = yuime_dim2_calculate_position(0.0f, 800.0f, btn.base->rect.w, btn.geometry.size->scale.x, btn.geometry.size->offset.x, btn.geometry.pivot.x);
	btn.base->rect.y = yuime_dim2_calculate_position(0.0f, 600.0f, btn.base->rect.h, btn.geometry.size->scale.y, btn.geometry.size->offset.y, btn.geometry.pivot.y);

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

		yuime_update(&ctx);

		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);

		yuime_render(&ctx);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	yuime_context_cleanup(&ctx);

	return 0;
}