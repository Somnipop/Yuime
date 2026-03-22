cmake_minimum_required(VERSION 3.10)
project(Yuime LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

option(BUILD_SHARED_LIBS "build as a shared library?" ON)
option(YUIME_BUILD_BASE_ONLY "build only the base?" OFF)

if (YUIME_BUILD_BASE_ONLY)
	file(GLOB YUIME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/base/*.c)
else()
	file(GLOB YUIME_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/base/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/src/elements/*.c
	)
endif()

if (BUILD_SHARED_LIBS)
	add_library(Yuime SHARED ${YUIME_SOURCES})
	target_compile_definitions(Yuime PRIVATE YUIME_EXPORT=1)
else()
	add_library(Yuime ${YUIME_SOURCE_FILES})
endif()

if (YUIME_BUILD_BASE_ONLY)
	target_compile_definitions(Yuime PUBLIC YUIME_BUILD_BASE_ONLY=1)
endif()

set_target_properties(Yuime PROPERTIES
	C_STANDARD 23
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
)

target_include_directories(Yuime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)