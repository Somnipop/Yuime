#pragma once

#include <SDL3/SDL.h>

#include <yuime/yuime.h>

int init(const yuime_vector2_t screen_size, yuime_context_t* ctx, SDL_Window** window, SDL_Renderer** renderer);