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

	yuime_node_t* panel1 = yuime_node_new(&ctx, NULL);
	yuime_node_t* panel1_btn = yuime_node_new(&ctx, panel1);
	yuime_node_t* panel1_btn2 = yuime_node_new(&ctx, panel1);

	yuime_node_t* panel2 = yuime_node_new(&ctx, NULL);
	yuime_node_t* panel2_btn = yuime_node_new(&ctx, panel2);
	yuime_node_t* panel2_btn2 = yuime_node_new(&ctx, panel2);

	yuime_node_free(&ctx, panel1_btn2);
	yuime_node_free(&ctx, panel2);

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

					ctx.screen_size.x = (float)w;
					ctx.screen_size.y = (float)h;
				}
			}
			if (event.type == SDL_EVENT_QUIT) {
				running = 0;
				break;
			}
		}

		// yuime_update(&ctx);

		SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
		SDL_RenderClear(renderer);

		// yuime_render(&ctx);

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