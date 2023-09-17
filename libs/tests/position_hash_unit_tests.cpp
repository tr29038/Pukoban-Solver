#include <catch2/catch_test_macros.hpp>

#include <position_hash.h>

#include <unordered_set>

TEST_CASE("position_hash")
{
    std::unordered_set<Position, Position_Hash> set;
    set.emplace(4, 3);
    set.emplace(4, 3);

    CHECK(set.count(Position(4, 3)) == 1);
}
