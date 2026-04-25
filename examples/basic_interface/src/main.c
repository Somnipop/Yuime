#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

#include "init.h"
#include "event_handler.h"
#include "mem_alloc.h"

inline void cleanup(SDL_Renderer *renderer, SDL_Window *window, yuime_context_t *ctx) {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	yuime_context_cleanup(ctx);

#ifndef NDEBUG
	mem_print_stats();
#endif // !NDEBUG
}

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

	yuime_dim2_t panel_dim = (yuime_dim2_t){
		.scale = (yuime_vector2_t){
			.x = 0.5f,
			.y = 0.5f,
		},
		.offset = (yuime_vector2_t){
			.x = 0.0f,
			.y = 0.0f
		}
	};

	// yuime_dim2_t btn_dim = (yuime_dim2_t){
	// 	.scale = (yuime_vector2_t){
	// 		.x = 0.5f,
	// 		.y = 0.5f,
	// 	},
	// 	.offset = (yuime_vector2_t){
	// 		.x = 0.0f,
	// 		.y = 0.0f
	// 	}
	// };

	YUIME_WIDGET(&ctx, panel, NULL, yuime_widget_panel_new_node, 0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 0.0f, &panel_dim);

	yuime_widget_panel_style_t panel_style = (yuime_widget_panel_style_t){
		.border = {
			.color = {.r=0, .g=0, .b=0, .a=255},
			.size = 2.0f
		}
	};
	((yuime_widget_panel_t*)panel->widget.widget)->style = &panel_style;

	// yuime_node_t *panel_btn = yuime_node_new(&ctx, panel, &btn_dim);

	// yuime_node_t *panel2 = yuime_node_new(&ctx, NULL, &panel_dim);

	// yuime_event_resize(&ctx, panel);
	// yuime_event_resize(&ctx, panel2);

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
					yuime_event_window_resize(&ctx, (yuime_vector2_t){(float)w, (float)h});
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

		yuime_render(&ctx);

		SDL_RenderPresent(renderer);
	}

	cleanup(renderer, window, &ctx);
	return 0;
}