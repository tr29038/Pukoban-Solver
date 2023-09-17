#pragma once

#include <position.h>

#include <optional>
#include <limits.h>

struct Node
{
    Node(Position _position, char _piece) : position(_position), piece(_piece) {}

    Position position;
    char piece;
};
