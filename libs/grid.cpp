#include "grid.h"

#include <pieces.h>
#include <state_astar_comparator.h>
#include <state_gfs_comparator.h>

#include <iostream>
#include <cstdlib>
#include <set>
#include <queue>
#include <stack>

//! @brief Convert the contents of grid_file into vector<string>.
//! @param grid_file The file path containing the grid puzzle contents.
Grid::Grid(const std::string& grid_file) :
    initial_state(Position(-1, -1), {}, {})
{
    initialize(grid_file);
}

//! @brief Print the state to the output stream.
//! @param state State to print.
//! @param output_stream Output stream to print to.
void Grid::print(const State& state, std::ostream& output_stream) const
{
    auto grid_copy(grid);

    for (const auto& storage_position : state.storage_positions)
        grid_copy[storage_position.y][storage_position.x].piece = piece_to_char(PIECES::STORAGE);
    for (const auto& box_position : state.box_positions)
        grid_copy[box_position.y][box_position.x].piece = piece_to_char(PIECES::BOX);
    grid_copy[state.robot_position.y][state.robot_position.x].piece = piece_to_char(PIECES::ROBOT);

    for (const auto& row : grid_copy)
    {
        for (const auto& node : row)
	{
            output_stream << node.piece;
	}
        output_stream << '\n';
    }
}

//! @brief Solve the pukoban puzzle.
//! @param algorithm The algorithm to solve the puzzle with.
//! @returns The populated state sequence solution to the puzzle from start to finish, if it is solveable. Else an empty vector.
std::vector<State> Grid::solve(const std::string& algorithm) const
{
    std::vector<State> result;
    if (algorithm == "dfs")
        result = depth_first_search();
    else if (algorithm == "bfs")
        result = breadth_first_search();
    else if (algorithm == "astar")
        result = astar();
    else if (algorithm == "gfs")
        result = greedy_first_search();
    else
        throw std::runtime_error("Invalid algorithm provided");

    return result;
}

//! @brief Breadth first search.
//! @return State solution path from start to goal.
std::vector<State> Grid::breadth_first_search() const
{
    std::unordered_map<State, State, State_Hash> came_from;
    std::unordered_set<State, State_Hash> closed_states;
    closed_states.insert(initial_state);
    std::queue<State> state_queue;
    state_queue.push(initial_state);
    while (!state_queue.empty())
    {
        auto current_state = state_queue.front();
        state_queue.pop();

        if (all_boxes_in_storage(current_state.box_positions, current_state.storage_positions))
            return build_path(came_from, current_state);

        std::vector<State> successor_states;
        for (auto direction : d.directions)
	{
            auto some_successor_states = get_legal_successor_states(current_state, direction);
            successor_states.insert(successor_states.end(), some_successor_states.begin(), some_successor_states.end());
	}
        for (const auto& successor_state : successor_states)
	{
            if (is_closed_state(closed_states, successor_state))
                continue;

            state_queue.push(successor_state);
            closed_states.insert(successor_state);
            came_from[successor_state] = current_state;
	}
    }

    return {};
}

//! @brief Depth first search.
//! @return State solution path from start to goal.
std::vector<State> Grid::depth_first_search() const
{
    std::unordered_map<State, State, State_Hash> came_from;
    std::unordered_set<State, State_Hash> closed_states;
    closed_states.insert(initial_state);
    std::stack<std::pair<State, std::vector<Position>>> state_stack;
    state_stack.emplace(initial_state, d.directions);
    while (!state_stack.empty())
    {
        auto [current_state, current_directions] = state_stack.top();
        state_stack.pop();

        if (all_boxes_in_storage(current_state.box_positions, current_state.storage_positions))
            return build_path(came_from, current_state);

        auto current_direction = current_directions.back();
        current_directions.pop_back();

        if (!current_directions.empty())
            state_stack.emplace(current_state, current_directions);

        auto successor_states = get_legal_successor_states(current_state, current_direction);
        for (const auto& successor_state : successor_states)
	{
            if (is_closed_state(closed_states, successor_state))
                continue;

            came_from[successor_state] = current_state;
            state_stack.emplace(successor_state, d.directions);
            closed_states.insert(successor_state);
        }
    }

    return {};
}

//! @brief A*.
//! @return State solution path from start to goal.
std::vector<State> Grid::astar() const
{
    std::shared_ptr<State_Comparator> comparator = std::make_shared<State_Astar_Comparator>();
    std::unordered_map<State, State, State_Hash> came_from;
    std::unordered_set<State, State_Hash> closed_states;
    std::priority_queue<State, std::vector<State>, State_Astar_Comparator> state_queue;
    state_queue.push(initial_state);
    while (!state_queue.empty())
    {
        auto current_state = state_queue.top();
        state_queue.pop();
        closed_states.insert(current_state);

        if (all_boxes_in_storage(current_state.box_positions, current_state.storage_positions))
            return build_path(came_from, current_state);

        for (auto direction : d.directions)
        {
            auto successor_states = get_legal_successor_states(current_state, direction);
            for (const auto& successor_state : successor_states)
	    {
                if (is_closed_state(closed_states, successor_state))
		{
                    auto successor_state_closed = std::find(closed_states.begin(), closed_states.end(), successor_state);
		    if (comparator->is_less_than(successor_state, *successor_state_closed))
                        closed_states.erase(successor_state_closed);
                    else
                        continue;
		}

                state_queue.push(successor_state);
                came_from.emplace(successor_state, current_state);
	    }
	}
    }

    return {};
}

//! @brief Greedy best-first search.
//! @return State solution path from start to goal.
std::vector<State> Grid::greedy_first_search() const
{
    std::unordered_map<State, State, State_Hash> came_from;
    std::shared_ptr<State_Comparator> comparator = std::make_shared<State_Gfs_Comparator>();
    std::unordered_set<State, State_Hash> closed_states;
    std::priority_queue<State, std::vector<State>, State_Gfs_Comparator> state_queue;
    state_queue.push(initial_state);
    while (!state_queue.empty())
    {
        auto current_state = state_queue.top();
        state_queue.pop();
        closed_states.insert(current_state);

        if (all_boxes_in_storage(current_state.box_positions, current_state.storage_positions))
            return build_path(came_from, current_state);

        for (auto direction : d.directions)
        {
            auto successor_states = get_legal_successor_states(current_state, direction);
            for (const auto& successor_state : successor_states)
	    {
                if (is_closed_state(closed_states, successor_state))
                    continue;

                state_queue.push(successor_state);
                came_from[successor_state] = current_state;
	    }
	}
    }

    return {};
}

//! @brief Get the successor state of a box push in direction.
//! @param state The state to succeed.
//! @param direction The direction to move the robot towards.
//! @return Successor state if possible, else std::nullopt.
std::optional<State> Grid::get_push_box_successor_state(State state, Position direction) const
{
    Position neighbor_position(state.robot_position.x + direction.x, state.robot_position.y + direction.y);

    // Ensure the robot is moving into a box.
    auto box_iter = std::find(state.box_positions.begin(), state.box_positions.end(), neighbor_position);
    if (box_iter == state.box_positions.end())
        return std::nullopt;

    // Ensure pushing the box will not go outside of the grid's boundaries.
    Position n_neighbor_position(neighbor_position.x + direction.x, neighbor_position.y + direction.y);
    if (!position_within_bounds(n_neighbor_position))
        return std::nullopt;

    // Ensure there is an open space to push the box into.
    if (!can_move_to_position(state, n_neighbor_position))
        return std::nullopt;

    box_iter->x += direction.x;
    box_iter->y += direction.y;
    state.robot_position.x += direction.x;
    state.robot_position.y += direction.y;
    ++state.current_total_distance_from_start;
    return state;
}

//! @brief Get the successor state of a regular robot move.
//! @param state The state to succeed.
//! @param direction The direction to move the robot towards.
//! @return Successor state if possible, else std::nullopt.
std::optional<State> Grid::get_normal_move_successor_state(State state, Position direction) const
{
    // Ensure there is an open space to move the robot into.
    Position neighbor_position(state.robot_position.x + direction.x, state.robot_position.y + direction.y);
    if (!can_move_to_position(state, neighbor_position))
        return std::nullopt;

    state.robot_position.x += direction.x;
    state.robot_position.y += direction.y;
    return state;
}

//! @brief Get the successor state of a box pull in direction.
//! @param state The state to succeed.
//! @param direction The direction to move the robot towards.
//! @return Successor state if possible, else std::nullopt.
std::optional<State> Grid::get_pull_box_successor_state(State state, Position direction) const
{
    // Ensure the robot will not go outside of the grid's boundaries.
    Position b_neighbor_position(state.robot_position.x - direction.x, state.robot_position.y - direction.y);
    if (!position_within_bounds(b_neighbor_position))
        return std::nullopt;

    // Ensure there is an adjacent box opposite the direction the robot is moving toward.
    auto b_box_iter = std::find(state.box_positions.begin(), state.box_positions.end(), b_neighbor_position);
    if (b_box_iter == state.box_positions.end())
        return std::nullopt;

    // Ensure there is an open space for the robot to back into.
    if (!get_normal_move_successor_state(state, direction).has_value())
        return std::nullopt;

    state.robot_position.x += direction.x;
    state.robot_position.y += direction.y;
    b_box_iter->x += direction.x;
    b_box_iter->y += direction.y;
    ++state.current_total_distance_from_start;
    return state;
}

//! @brief Get all legal successor states (push, pull, regular).
//! @param state The state to derive from.
//! @param direction The direction to move the robot towards.
//! @return All legal successor states.
std::vector<State> Grid::get_legal_successor_states(const State& state, Position direction) const
{
    std::vector<State> legal_successor_states;

    // Ensure moving the robot will not result in outside grid bounadries.
    Position neighbor_position(state.robot_position.x + direction.x, state.robot_position.y + direction.y);
    if (!position_within_bounds(neighbor_position))
        return legal_successor_states;

    // Push box if able.
    auto state_push_box = get_push_box_successor_state(state, direction);
    if (state_push_box.has_value())
        legal_successor_states.push_back(state_push_box.value());

    // Move without a box if able.
    auto state_normal_move = get_normal_move_successor_state(state, direction);
    if (state_normal_move.has_value())
        legal_successor_states.push_back(state_normal_move.value());

    // Pull box if able.
    auto state_pull_box = get_pull_box_successor_state(state, direction);
    if (state_pull_box.has_value())
        legal_successor_states.push_back(state_pull_box.value());

    return legal_successor_states;
}

//! @brief Construct state path from the goal state until no more links are found.
//! @param came_from A state mapping of linked states.
//! @param goal_state The goal state to begin the path construction from.
//! @return The constructed state path.
std::vector<State> Grid::build_path(std::unordered_map<State, State, State_Hash>& came_from, const State& goal_state) const
{
    std::vector<State> path;
    auto current_state = goal_state;
    while (came_from.find(current_state) != came_from.end())
    {
        path.push_back(current_state);
        current_state = came_from[current_state];
    }
    path.push_back(current_state);
    return path;
}

//! @brief Check if the robot is on position.
//! @param state The state to inspect.
//! @param position The position to check if the robot is on.
//! @return True if the robot is on position. False if not.
bool Grid::robot_is_on_position(const State& state, Position position) const
{
    return state.robot_position == position;
}

//! @brief Check if any box is on position.
//! @param state The state to inspect.
//! @param position The position to check if a box is on.
//! @return True if a box is on position. False if not.
bool Grid::box_is_on_position(const State& state, Position position) const
{
    return std::find(state.box_positions.begin(), state.box_positions.end(), position) != state.box_positions.end();
}

//! @brief Check if position is a valid place to move a piece to.
//! @param state The state to inspect.
//! @param position The position to check.
//! @return True if the move is valid. False otherwise.
bool Grid::can_move_to_position(const State& state, Position position) const
{
    auto will_move_into_obstruction = obstruction_at_position(position);
    return !robot_is_on_position(state, position) && !box_is_on_position(state, position) && !will_move_into_obstruction;
}

//! @brief Check if state is closed from searching.
//! @param closed_states The collection of closed states.
//! @param state The state to check.
//! @return True if the state is closed. False otherwise.
bool Grid::is_closed_state(const std::unordered_set<State, State_Hash>& closed_states, const State& state) const
{
    return closed_states.count(state) > 0;
}

//! @brief Check if all box positions cover all storage positions.
//! @param box_positions Positions of boxes.
//! @param storage_positions Positions of storages.
//! @returns True if all boxes are in storage. False otherwise.
bool Grid::all_boxes_in_storage(const std::vector<Position>& box_positions, const std::vector<Position>& storage_positions) const
{
    for (const auto& box_position : box_positions)
    {
        if (std::find(storage_positions.begin(), storage_positions.end(), box_position) == storage_positions.end())
            return false;
    }

    return true;
}

//! @brief Check if position is an obstruction piece.
//! @param position Position to check.
//! @return True if position is an obstruction piece. False otherwise.
bool Grid::obstruction_at_position(Position position) const
{
    return grid[position.y][position.x].piece == piece_to_char(PIECES::OBSTRUCTION);
}

//! @brief Determine if position is within bounds of the grid.
//! @param position The position to check for.
//! @returns True if position is within the grid's boundaries. False if it's not.
bool Grid::position_within_bounds(Position position) const
{
    return position_within_bounds(position.x, position.y);
}

//! @brief Determine if position is within bounds of the grid.
//! @param x X coordinate to check for.
//! @param y Y coordinate to check for.
//! @returns True if position is within the grid's boundaries. False if its not.
bool Grid::position_within_bounds(int x, int y) const
{
    return (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size());
}

//! @brief Convert piece from PIECES type to char type.
//! @param piece Data to convert.
//! @returns Char version of piece.
char Grid::piece_to_char(PIECES piece) const
{
    return static_cast<char>(piece);
}

//! @brief Convert piece from char to PIECES type.
//! @param piece Data to convert.
//! @returns PIECES version of piece.
PIECES Grid::char_to_piece(char piece) const
{
    return static_cast<PIECES>(piece);
}

//! @brief Initialize the grid given the grid input file path.
//! @param grid_file File path to the grid puzzle.
//! @throw std::runtime_error If grid.size == 0 or grid[0].size == 0.
//! @throw std::runtime_error If robots > 1.
//! @throw std::runtime_error If storages == 0 or boxes == 0.
//! @throw std::runtime_error If storages != boxes.
//! @throw std::runtime_error If an invalid character is found in the grid file.
void Grid::initialize(const std::string& grid_file)
{
    std::ifstream file_stream(grid_file);

    int number_of_robots = 0, number_of_storages = 0, number_of_boxes = 0;
    int number_of_obstructions = 0, number_of_blanks = 0;

    // Read the file stream line by line.
    while (file_stream.peek() != EOF)
    {
        std::string row_str;
        std::getline(file_stream, row_str);
        std::vector<Node> row;
        for (char piece : row_str)
	{
            PIECES piece_non_char = char_to_piece(piece);
            if (State::is_state_piece(piece_non_char))
	    {
                if (char_to_piece(piece) == PIECES::ROBOT)
		{
                    initial_state.robot_position = Position(row.size(), grid.size());
		    ++number_of_robots;
		}
                else if (char_to_piece(piece) == PIECES::BOX)
		{
                    initial_state.box_positions.emplace_back(row.size(), grid.size());
		    ++number_of_boxes;
		}
                else if (char_to_piece(piece) == PIECES::STORAGE)
		{
                    initial_state.storage_positions.emplace_back(row.size(), grid.size());
		    ++number_of_storages;
		}
                row.emplace_back(Position(row.size(), grid.size()), piece_to_char(PIECES::BLANK));
	    }
            else
	    {
                if (piece_non_char == PIECES::OBSTRUCTION)
                    ++number_of_obstructions;
		else if (piece_non_char == PIECES::BLANK)
                    ++number_of_blanks;
                row.emplace_back(Position(row.size(), grid.size()), piece);
	    }
	}
        grid.push_back(row);
    }

    file_stream.close();

    // Validation.
    if (grid.empty() || grid[0].empty()) throw std::runtime_error("The grid must have a dimension of MxN where M > 0 and N > 0");
    if (number_of_robots != 1) throw std::runtime_error("There must be one and only one robot in the puzzle");
    if (number_of_storages == 0) throw std::runtime_error("There must be at least one storage in the puzzle");
    if (number_of_boxes == 0) throw std::runtime_error("There must be at least one box in the puzzle");
    if (number_of_storages != number_of_boxes) throw std::runtime_error("There must be an equal number of storages and boxes in the puzzle");
    int total_valid_pieces = number_of_obstructions + number_of_blanks + number_of_robots + number_of_storages + number_of_boxes;
    if (total_valid_pieces != grid.size() * grid[0].size()) throw std::runtime_error("Invalid character found in the puzzle");
}
