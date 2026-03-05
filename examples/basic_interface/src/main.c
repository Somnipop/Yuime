#define YUIME_IMPLEMENTATION
#include "yuime/yuime.h"

int main() {
	yuime_element_button btn = {
		.minSize = {0.0f, 0.0f},
		.maxSize = {255.0f, 255.0f},
	
		.geometry = {
				.pivot = {0.5f, 0.05f},
				.position = {
					.scale = {0.5f, 0.5f},
					.offset = {0.0f, 0.0f}
				},
				.size = {
					.scale = {0.5f, 0.5f},
					.offset = {0.0f, 0.0f}
				}
		}
	};
}