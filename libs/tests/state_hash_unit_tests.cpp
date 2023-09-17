#include <catch2/catch_test_macros.hpp>

#include <state_hash.h>

#include <unordered_set>

TEST_CASE("state_hash")
{
    std::unordered_set<State, State_Hash> set;
    State state(
        Position(4, 3),
        { Position(5, 5), Position(1, 1) },
        { Position(2, 2), Position(1, 2) }
    );

    set.insert(state);
    set.insert(state);

    CHECK(set.count(state) == 1);
}
