#include <catch2/catch_test_macros.hpp>

#include <state_gfs_comparator.h>

TEST_CASE("gfs_is_less_than")
{
    State_Gfs_Comparator comparator;

    State s1(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 5), Position(1, 1) }
    );

    State s2(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 6), Position(1, 1) }
    );

    CHECK(comparator.is_less_than(s1, s2) == true);
}

TEST_CASE("gfs_is_greater_than")
{
    State_Gfs_Comparator comparator;

    State s1(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 8), Position(3, 5) }
    );

    State s2(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(5, 6), Position(2, 2) }
    );

    CHECK(comparator.is_greater_than(s1, s2) == true);
}
