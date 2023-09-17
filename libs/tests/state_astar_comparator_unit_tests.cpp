#include <catch2/catch_test_macros.hpp>

#include <state_astar_comparator.h>

TEST_CASE("astar_is_less_than")
{
    State_Astar_Comparator comparator;

    State s1(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 5), Position(1, 1) }
    );
    s1.current_total_distance_from_start = 10;

    State s2(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 4), Position(1, 1) }
    );
    s2.current_total_distance_from_start = 3;

    CHECK(comparator.is_less_than(s2, s1) == true);
}

TEST_CASE("astar_is_greater_than")
{
    State_Astar_Comparator comparator;

    State s1(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(3, 8), Position(3, 5) }
    );
    s1.current_total_distance_from_start = 4;

    State s2(
        Position(0, 0),
        { Position(3, 4), Position(0, 1) },
        { Position(5, 6), Position(2, 2) }
    );
    s2.current_total_distance_from_start = 12;

    CHECK(comparator.is_greater_than(s2, s1) == true);
}
