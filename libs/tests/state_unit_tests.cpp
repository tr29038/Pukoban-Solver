#include <catch2/catch_test_macros.hpp>

#include <state.h>

#include <sstream>

TEST_CASE("state_constructor_default")
{
    State state;
}

TEST_CASE("state_constructor_not_default")
{
    State state(
        Position(5, 5),
        { Position(1, 1) },
        { Position(4, 4) }
    );
}

TEST_CASE("state_equals")
{
    State state1;
    State state2;

    CHECK(state1 == state2);
}

TEST_CASE("state_not_equals")
{
    State state1;
    State state2(Position(5, 5), {}, {});

    CHECK(state1 != state2);
}

TEST_CASE("is_state_piece")
{
    CHECK(State::is_state_piece(PIECES::ROBOT) == true);
}

TEST_CASE("is_not_state_piece")
{
    CHECK(State::is_state_piece(PIECES::OBSTRUCTION) == false);
}

TEST_CASE("state_output_stream")
{
    State state(
        Position(3, 3),
        { Position(5, 4), Position(1, 2) },
        { Position(1, 1), Position(8, 9) }
    );

    std::stringstream ss;
    ss << state;

    CHECK(ss.str() == "robot_position: 3,3 box_position: 5,4 box_position: 1,2 storage_position: 1,1 storage_position: 8,9 ");
}
