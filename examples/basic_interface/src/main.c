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

	yuime_dim2_t btn_dim = (yuime_dim2_t){
		.scale = (yuime_vector2_t){
			.x = 0.5f,
			.y = 0.5f,
		},
		.offset = (yuime_vector2_t){
			.x = 0.0f,
			.y = 0.0f
		}
	};

	yuime_style_t style = (yuime_style_t){
		.color = (yuime_color_t){
			.r = 0,
			.g = 0,
			.b = 0,
			.a = 255
		},
		.border = (yuime_style_border_t){
			.color = (yuime_color_t){
				.r = 0,
				.g = 255,
				.b = 0,
				.a = 255
			},
			.radius = 10.0f,
			.size = 2.0f
		}
	};

	yuime_node_t *panel = yuime_node_new(&ctx, NULL, &panel_dim, &style);
	{	
		panel->geometry.pivot.x = 0.0f;
		panel->geometry.pivot.y = 0.0f;

		panel->geometry.position.scale.x = 0.0f;
		panel->geometry.position.offset.x = 0.0f;

		panel->geometry.position.scale.y = 0.0f;
		panel->geometry.position.offset.y = 0.0f;
	}

	yuime_node_t *panel_btn = yuime_node_new(&ctx, panel, &btn_dim, &style);
	{
		panel_btn->geometry.pivot.x = 0.5f;
		panel_btn->geometry.pivot.y = 0.5f;

		panel_btn->geometry.position.scale.x = 0.5f;
		panel_btn->geometry.position.offset.x = 0.0f;

		panel_btn->geometry.position.scale.y = 0.5f;
		panel_btn->geometry.position.offset.y = 0.0f;
	}

	yuime_node_t *panel2 = yuime_node_new(&ctx, NULL, &panel_dim, &style);
	{
		panel2->geometry.pivot.x = 1.0f;
		panel2->geometry.pivot.y = 1.0f;
	
		panel2->geometry.position.scale.x = 1.0f;
		panel2->geometry.position.offset.x = 0.0f;
	
		panel2->geometry.position.scale.y = 1.0f;
		panel2->geometry.position.offset.y = 0.0f;
	}

	yuime_node_update_rect(&ctx, panel);
	yuime_node_update_rect(&ctx, panel2);

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
					if (ctx.node_tree != NULL) {
						yuime_node_t *node = ctx.node_tree;
						while (node != NULL) {
							yuime_node_update_rect(&ctx, node);
							node = node->next;
						}
					}
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