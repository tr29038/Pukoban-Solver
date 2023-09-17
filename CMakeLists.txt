cmake_minimum_required(VERSION 3.5)
project(pukoban_solver)

include_directories(pukoban_solver ${CMAKE_CURRENT_SOURCE_DIR}/libs)

add_executable(pukoban_solver main.cpp)

target_link_libraries(pukoban_solver grid)

add_subdirectory(./libs)
