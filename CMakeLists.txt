cmake_minimum_required(VERSION 3.10)
project(Yuime LANGUAGES C)

option(BUILD_SHARED_LIBS "Whether should build as a shared library or static" ON)

file(GLOB YUIME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

if (BUILD_SHARED_LIBS)
	add_library(Yuime SHARED ${YUIME_SOURCES})
	target_compile_definitions(Yuime PRIVATE YUIME_EXPORT=1)
else()
	add_library(Yuime ${YUIME_SOURCE_FILES})
endif()

set_target_properties(Yuime PROPERTIES
	C_STANDARD 23
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
)

target_include_directories(Yuime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)