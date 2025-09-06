cmake_minimum_required(VERSION 3.15)
project(bxn C)

add_subdirectory(thirdparty/glfw)

file(GLOB_RECURSE BXN_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(bxn ${BXN_SOURCES})
target_include_directories(bxn
    PUBLIC src
    PUBLIC thirdparty/glfw/include
)

target_link_libraries(bxn PRIVATE glfw)
