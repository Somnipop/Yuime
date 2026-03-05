file(GLOB BASIC_INTERFACE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/basic_interface/src/*.c)
add_executable(basic_interface ${BASIC_INTERFACE_SOURCES})
target_link_libraries(basic_interface Yuime)
target_compile_definitions(basic_interface PUBLIC YUIME_IMPORT=1)