#pragma once

#include <ostream>

struct Position
{
    Position(int _x, int _y) : x(_x), y(_y) {}
    Position() {}
    ~Position() = default;

    bool operator==(const Position p) const { return x == p.x && y == p.y; }
    bool operator!=(const Position p) const { return !(*this == p); }
    bool operator==(Position p) { return x == p.x && y == p.y; }
    bool operator!=(Position p) { return !(*this == p); }

    int x, y;
};

std::ostream& operator<<(std::ostream&, Position);
