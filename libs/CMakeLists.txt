cmake_minimum_required(VERSION 3.5)
project(grid)

set(grid_SRCS grid.h grid.cpp position.h position.cpp position_hash.h position_hash.cpp pieces.h node.h directions.h directions.cpp state.h state.cpp state_hash.h state_hash.cpp state_comparator.h state_comparator.cpp state_astar_comparator.h state_astar_comparator.cpp state_gfs_comparator.h state_gfs_comparator.cpp)

add_library(grid SHARED ${grid_SRCS})

if(BUILD_TESTING)
    add_executable(unit_tests ${grid_SRCS} tests/grid_unit_tests.cpp tests/position_unit_tests.cpp tests/position_hash_unit_tests.cpp tests/node_unit_tests.cpp tests/state_hash_unit_tests.cpp tests/state_unit_tests.cpp tests/directions_unit_tests.cpp tests/state_gfs_comparator_unit_tests.cpp tests/state_astar_comparator_unit_tests.cpp)

    find_package(Catch2 3 REQUIRED)

    target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
endif()
