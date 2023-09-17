cmake_minimum_required(VERSION 3.5)
project(unit_tests)

add_executable(unit_tests grid_tests.cpp)

find_package(Catch2 3 REQUIRED)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(unit_tests grid)
