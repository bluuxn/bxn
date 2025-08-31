cmake_minimum_required(VERSION 3.15)
project(bxn C)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/cglm)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)

add_library(bxn ${SOURCES})
target_include_directories(bxn PUBLIC src)

target_link_libraries(bxn PRIVATE glfw PRIVATE cglm)
