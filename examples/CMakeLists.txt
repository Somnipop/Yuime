add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SDL EXCLUDE_FROM_ALL)

set(SHARED_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/shared/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/shared/src/renderers/*.c
)

file(GLOB BASIC_INTERFACE_SOURCES
	${SHARED_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/basic_interface/src/*.c
)
add_executable(basic_interface ${BASIC_INTERFACE_SOURCES})

target_include_directories(basic_interface PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/shared/src)

target_link_libraries(basic_interface PRIVATE Yuime SDL3::SDL3)
target_compile_definitions(basic_interface PUBLIC YUIME_IMPORT=1)