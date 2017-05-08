cmake_minimum_required(VERSION 2.8)

project(The2048)

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} main.cxx game.cxx)
target_link_libraries(The2048 con_color fileIO)
