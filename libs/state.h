#pragma once

#include <position.h>
#include <pieces.h>
#include <state_comparator.h>

#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <limits.h>

class State_Comparator;

struct State
{
    State(Position _robot_position,
          const std::vector<Position>& _box_positions,
          const std::vector<Position>& _storage_positions) :
        robot_position(_robot_position),
        box_positions(_box_positions),
        storage_positions(_storage_positions) {}

    State() : robot_position(Position(0, 0)), box_positions({}), storage_positions({}) {}

    bool operator==(State&);
    bool operator!=(State&);
    bool operator==(const State&) const;
    bool operator!=(const State&) const;

    static bool is_state_piece(PIECES);

    Position robot_position;
    std::vector<Position> box_positions;
    std::vector<Position> storage_positions;

    // Property for A*.
    int current_total_distance_from_start = 0;

    private:
        bool is_equal(const State&, const State&) const;
};

std::ostream& operator<<(std::ostream&, const State&);
