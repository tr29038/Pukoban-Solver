#pragma once

#include <position.h>
#include <state.h>
#include <position_hash.h>

#include <unordered_set>

class State;

class State_Comparator
{
    public:
        virtual bool operator()(const State&, const State&) const = 0;

        virtual bool is_greater_than(const State&, const State&) const = 0;
        virtual bool is_less_than(const State&, const State&) const = 0;

    protected:
        int get_manhattan_distance(Position, Position) const;
        int get_nearest_storage_distance(const State&, Position) const;
        int get_number_of_stored_boxes(const State&) const;
        bool has_box(const State&, Position) const;
        int get_total_manhattan_distances(const State&) const;
};
