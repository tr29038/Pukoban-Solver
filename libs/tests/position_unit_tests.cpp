#include <catch2/catch_test_macros.hpp>

#include <position.h>

#include <sstream>

TEST_CASE("position_constructor")
{
    Position position(5, 4);

    CHECK(position.x == 5);
    CHECK(position.y == 4);
}

TEST_CASE("position_equals")
{
    Position pos1(4, 3);
    Position pos2(4, 3);

    CHECK(pos1 == pos2);
}

TEST_CASE("position_not_equals")
{
    Position pos1(4, 4);
    Position pos2(3, 2);

    CHECK(pos1 != pos2);
}

TEST_CASE("position_output_stream")
{
    Position pos(5, 5);
    std::stringstream ss;
    ss << pos;

    CHECK(ss.str() == "5,5");
}
