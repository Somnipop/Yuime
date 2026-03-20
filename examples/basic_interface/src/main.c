#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

#include "init.h"
#include "mem_alloc.h"

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	yuime_context ctx;

	init(&ctx, &window, &renderer);

	yuime_dim2 size = {
		.scale = {0.33f, 0.33f},
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

	yuime_element_button btn[3];

	// TOP LEFT
	yuime_element_button_init(&ctx, &btn[0], (yuime_geometry){
				.pivot = {0.0f, 0.0f},
				.position = {
					.scale = {0.0f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, YUIME_ELEMENT_FLAG_NONE
	);

	// TOP CENTER
	yuime_element_button_init(&ctx, &btn[1], (yuime_geometry){
				.pivot = {0.5f, 0.0f},
				.position = {
					.scale = {0.5f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, YUIME_ELEMENT_FLAG_NONE
	);

	// TOP RIGHT
	yuime_element_button_init(&ctx, &btn[2], (yuime_geometry){
				.pivot = {1.0f, 0.0f},
				.position = {
					.scale = {1.0f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, YUIME_ELEMENT_FLAG_NONE
	);

	{
		yuime_rect screen_rect = {
			.x = 0.0f,
			.y = 0.0f,
			.w = 800.0f,
			.h = 600.0f
		};
	
		for (uint8_t i = 0; i < sizeof(btn)/sizeof(btn[0]); ++i) {
			yuime_set_visibility(&ctx.memory, &btn[i].base, 1);
			yuime_geometry_calculate_rect(&btn[i].geometry, &screen_rect, &btn[i].base.rect);
		}
	}

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

#ifndef NDEBUG
	mem_print_stats();
#endif // !NDEBUG
	return 0;
}