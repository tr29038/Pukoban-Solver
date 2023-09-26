#pragma once

#include <position.h>
#include <state.h>
#include <position_hash.h>

#include <list>
#include <unordered_set>

class State;

class State_Comparator
{
    public:
        virtual bool operator()(const State&, const State&) const = 0;

        virtual bool is_greater_than(const State&, const State&) const = 0;
        virtual bool is_less_than(const State&, const State&) const = 0;

        int get_heuristic_value(const State&) const;

    protected:
        int get_manhattan_distance(Position, Position) const;
        int get_robot_to_nearest_box_distance(const State&) const;
        std::list<std::tuple<std::string, std::string, int>> get_distances(const State&) const;
};
