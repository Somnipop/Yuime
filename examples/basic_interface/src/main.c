#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

#include "init.h"
#include "event_handler.h"
#include "mem_alloc.h"

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	yuime_context_t ctx;

	{
		int result = init((yuime_vector2_t){1280, 720}, &ctx, &window, &renderer);
		if (result != 0) {
			return result;
		}
	}

	yuime_dim2_t size = {
		.scale = {0.33f, 0.33f},
		.offset = {0.0f, 0.0f}
	};

	// yuime_element_button_t btn;
	// yuime_element_button_init(&ctx, &btn, (yuime_geometry_t){
	// 				.pivot = {0.5f, 0.5f},
	// 				.position = {
	// 					.scale = {0.5f, 0.5f},
	// 					.offset = {0.0f, 0.0f}
	// 				},
	// 				.size = &size
	// 		}, YUIME_ELEMENT_FLAG_NONE);

	yuime_element_button_t btn[3];

	// TOP LEFT
	yuime_element_button_init(&ctx, &btn[0], (yuime_geometry_t){
				.pivot = {0.0f, 0.0f},
				.position = {
					.scale = {0.0f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, element_event_callback, YUIME_ELEMENT_FLAG_NONE
	);

	// TOP CENTER
	yuime_element_button_init(&ctx, &btn[1], (yuime_geometry_t){
				.pivot = {0.5f, 0.0f},
				.position = {
					.scale = {0.5f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, element_event_callback, YUIME_ELEMENT_FLAG_NONE
	);

	// TOP RIGHT
	yuime_element_button_init(&ctx, &btn[2], (yuime_geometry_t){
				.pivot = {1.0f, 0.0f},
				.position = {
					.scale = {1.0f, 0.0f},
					.offset = {0.0f, 0.0f}
				},
				.size = &size
		}, element_event_callback, YUIME_ELEMENT_FLAG_NONE
	);

	{
		yuime_rect_t screen_rect = (yuime_rect_t){
			0,
			0,
			ctx.screen_size.x,
			ctx.screen_size.y
		};

		for (uint8_t i = 0; i < sizeof(btn)/sizeof(btn[0]); ++i) {
			yuime_set_visibility(&ctx.memory, &btn[i].base, 1);
		}
	}

	example_event_t example_event;
	memset(&example_event, 0, sizeof(example_event_t));

	SDL_Event event;
	uint8_t running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
				case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
				case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
				case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
				case SDL_EVENT_WINDOW_MAXIMIZED:
				case SDL_EVENT_WINDOW_MINIMIZED:
				case SDL_EVENT_WINDOW_RESIZED: {
					// TODO: which one?
					// SDL_GetWindowSizeInPixels();
					// SDL_GetWindowSize();
					int w, h;
					SDL_GetWindowSizeInPixels(window, &w, &h);

					example_event.type = EVENT_WINDOW_RESIZE;
					example_event.window.width = (float)w;
					example_event.window.height = (float)h;

					ctx.screen_size.x = example_event.window.width;
					ctx.screen_size.y = example_event.window.height;

					ctx.event_callback(&ctx, YUIME_EVENT_RESIZE, &renderer);
				}
			}
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