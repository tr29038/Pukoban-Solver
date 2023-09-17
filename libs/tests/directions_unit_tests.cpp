#include <catch2/catch_test_macros.hpp>

#include <directions.h>

#include <algorithm>

TEST_CASE("directions_constructor")
{
    Directions d;

    std::vector<Position> expected_directions;
    expected_directions.emplace_back(1, 0);
    expected_directions.emplace_back(-1, 0);
    expected_directions.emplace_back(0, 1);
    expected_directions.emplace_back(0, -1);

    for (auto expected_direction : expected_directions)
        CHECK(std::find(d.directions.begin(), d.directions.end(), expected_direction) != d.directions.end());
}
