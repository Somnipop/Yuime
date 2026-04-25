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

static inline uint8_t handle_events(SDL_Window *window, yuime_context_t *ctx) {
	static SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// TODO: does all of these window events actually matter to window resize?
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
				yuime_event_window_resize(ctx, YUIME_VEC2(w, h));
			}
		}
		if (event.type == SDL_EVENT_QUIT) {
			return 0;
		}
	}

	return 1;
}

static inline void render(SDL_Renderer *renderer, yuime_context_t *ctx) {
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	yuime_render(ctx);

	SDL_RenderPresent(renderer);
}

int main() {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	yuime_context_t ctx;
	{
		int result = init(YUIME_VEC2(1280, 720), &ctx, &window, &renderer);
		if (result != 0) {
			return result;
		}
	}

	yuime_dim2_t panel_dim = YUIME_DIM2(
		0.5f, 0,
		0.5f, 0
	);

	yuime_node_t *panel = NULL;
	YUIME_WIDGET_PANEL(&ctx, panel, NULL, YUIME_GEOMETRY(
			0.5f, 0.5f, // PIVOT
			0.5f, 0, // POSITION X
			0.5f, 0, // POSITION Y
			&panel_dim // SIZE
	));

	// WE ARE NOT DOING A STYLE SYSTEM. This library is
	// supposed to be simple but powerful. If you wish
	// to use a style handler make your own.
	yuime_widget_panel_style_t panel_style = {0};
	panel_style.border.color = YUIME_COLOR(0,0,0,255);
	panel_style.border.size = 2.0f;

	YUIME_NODE_WIDGET(yuime_widget_panel_t, panel)->style = &panel_style;

	while (1) {
		if (!handle_events(window, &ctx)) {
			break;
		}

		render(renderer, &ctx);
	}

	cleanup(renderer, window, &ctx);
	return 0;
}