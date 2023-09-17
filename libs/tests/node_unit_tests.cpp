#include <catch2/catch_test_macros.hpp>

#include <node.h>
#include <position.h>

TEST_CASE("node_constructor")
{
    Node node(Position(0, 0), 'R');
}
