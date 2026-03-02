cmake_minimum_required(VERSION 3.10)
project(Yuime)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Whether should build as a shared library or static" ON)

file(GLOB YUIME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

if (BUILD_SHARED_LIBS)
	add_library(Yuime SHARED ${YUIME_SOURCES})
	target_compile_definitions(Yuime PRIVATE YUIME_EXPORT=1)
else()
	add_library(Yuime ${YUIME_SOURCE_FILES})
endif()

target_include_directories(Yuime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)