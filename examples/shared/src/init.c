#include "init.h"

#include <stdio.h>

#include "mem_alloc.h"
#include "render.h"

int init(yuime_context* ctx, SDL_Window** window, SDL_Renderer** renderer) {
	if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMEPAD)) {
		printf("Failed to initialize SDL\n");
		return 1;
	}

	*window = SDL_CreateWindow("basic_interface", 800, 600, SDL_WINDOW_RESIZABLE);
	if (!(*window)) {
		printf("Failed to create window\n");
		return 1;
	}

	*renderer = SDL_CreateRenderer(*window, NULL);
	if (!(*renderer)) {
		printf("Failed to create renderer\n");
		return 1;
	}

	yuime_context_init(
		ctx,
		(yuime_memory_functions){
			mem_alloc,
			mem_realloc,
			mem_free
		},

		// TODO: instead of calling render_element every element render call, make yuime return a list of elements to be drawn to the screen.
		(yuime_render_callback){
			.data = renderer,
			.element = render_element
		}
	);

	return 0;
}