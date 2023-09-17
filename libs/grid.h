#pragma once

#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <unordered_set>

#include <position.h>
#include <node.h>
#include <directions.h>
#include <pieces.h>
#include <state.h>
#include <state_hash.h>

class Grid
{
    public:
        Grid(const std::string&);
        ~Grid() = default;

        Grid() = delete;

	std::vector<State> solve(const std::string&) const;
        void print(const State&, std::ostream&) const;

    private:
        std::vector<State> breadth_first_search() const;
        std::vector<State> depth_first_search() const;
        std::vector<State> astar() const;
        std::vector<State> greedy_first_search() const;
        std::optional<State> get_push_box_successor_state(State, Position) const;
        std::optional<State> get_normal_move_successor_state(State, Position) const;
        std::optional<State> get_pull_box_successor_state(State, Position) const;
        std::vector<State> get_legal_successor_states(const State&, Position) const;
        std::vector<State> build_path(std::unordered_map<State, State, State_Hash>&, const State&) const;
        bool robot_is_on_position(const State&, Position) const;
        bool box_is_on_position(const State&, Position) const;
        bool can_move_to_position(const State&, Position) const;
        bool is_closed_state(const std::unordered_set<State, State_Hash>&, const State&) const;
        bool all_boxes_in_storage(const std::vector<Position>&, const std::vector<Position>&) const;
        bool obstruction_at_position(Position) const;
        bool position_within_bounds(Position) const;
        bool position_within_bounds(int, int) const;
        char piece_to_char(PIECES) const;
        PIECES char_to_piece(char) const;
        void initialize(const std::string&);

        std::vector<std::vector<Node>> grid;
        State initial_state;
        Directions d;
};
