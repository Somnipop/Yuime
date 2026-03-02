#pragma once

#ifdef _WIN32
	#ifdef YUIME_EXPORT
		#define YUIME_API __declspec(dllexport)
	#elif defined(YUIME_IMPORT)
		#define YUIME_API __declspec(dllimport)
	#endif
#elif defined(YUIME_EXPORT)
	#define YUIME_API __attribute__((visibility("default")))
#endif

#ifndef YUIME_API
#define YUIME_API
#endif