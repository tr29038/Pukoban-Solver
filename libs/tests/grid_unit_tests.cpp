#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>

#include <grid.h>

#include <queue>

const std::string puzzles_test_dir = "../../puzzles/testers/";
const std::string puzzles_dir = "../../puzzles/";

TEST_CASE("grid_constructor")
{
    Grid grid(puzzles_dir + "puzzle_1.txt");
}

TEST_CASE("grid_invalid_init_empty_puzzle")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "empty.txt"));
}

TEST_CASE("grid_invalid_init_no_robot")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "no_robot.txt"));
}

TEST_CASE("grid_invalid_init_multiple_robots")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "multiple_robots.txt"));
}

TEST_CASE("grid_invalid_init_no_storage")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "no_storage.txt"));
}

TEST_CASE("grid_invalid_init_no_box")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "no_box.txt"));
}

TEST_CASE("grid_invalid_init_unequal_storage_and_box")
{
    CHECK_THROWS(Grid(puzzles_test_dir + "unequal_storage_box.txt"));
}

TEST_CASE("grid_unsolveable")
{
    Grid grid(puzzles_test_dir + "not_possible.txt");
    auto path = grid.solve("astar");

    CHECK(path.empty());
}

TEST_CASE("bfs_solves")
{
    Grid grid(puzzles_dir + "puzzle_7.txt");
    auto path = grid.solve("bfs");

    CHECK(!path.empty());
}

TEST_CASE("dfs_solves")
{
    Grid grid(puzzles_dir + "puzzle_7.txt");
    auto path = grid.solve("dfs");

    CHECK(!path.empty());
}

TEST_CASE("gfs_solves")
{
    Grid grid(puzzles_dir + "puzzle_1.txt");
    auto path = grid.solve("gfs");

    CHECK(!path.empty());
}

TEST_CASE("astar_solves")
{
    Grid grid(puzzles_dir + "puzzle_5.txt");
    auto path = grid.solve("astar");

    CHECK(!path.empty());
}
