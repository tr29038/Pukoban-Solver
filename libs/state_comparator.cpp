#include "state_comparator.h"

//! @brief Get the manhattan distance between two positions/points.
//! @param p1 One of the positions.
//! @param p2 One of the positions.
//! @return The manhattan distance between the two positions.
int State_Comparator::get_manhattan_distance(Position p1, Position p2) const
{
   return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

//! @brief Get the distance from the box position to the storage position nearest to it.
//! @param s The state containing the storage positions.
//! @param box_position The box position.
//! @return The distance from the box position to the storage position nearest to it.
int State_Comparator::get_nearest_storage_distance(const State& s, Position box_position) const
{
    int shortest_distance = INT_MAX;
    for (auto iter = s.storage_positions.begin(); iter != s.storage_positions.end(); ++iter)
    {
        //if (has_box(s, *iter))
        //    continue;

        auto distance = get_manhattan_distance(*iter, box_position);
        if (distance < shortest_distance)
            shortest_distance = distance;
    }

    return shortest_distance;
}

//! @brief Get the number of boxes in storage.
//! @param s The state to consider.
//! @return The number of boxes in storage.
int State_Comparator::get_number_of_stored_boxes(const State& s) const
{
    int num_stored = 0;
    for (auto box_position : s.box_positions)
        num_stored += std::find(s.storage_positions.begin(), s.storage_positions.end(), box_position) != s.storage_positions.end();
    return num_stored;
}

//! @brief Check if the storage has a box on it.
//! @param s The state containing the box positions.
//! @param storage_position The position of the storage to check.
//! @return True if box is on storage. False otherwise.
bool State_Comparator::has_box(const State& s, Position storage_position) const
{
    return std::find(s.box_positions.begin(), s.box_positions.end(), storage_position) != s.box_positions.end();
}

//! @brief Get the total distance from each box to each storage position nearest to it.
//! @param s The state to consider.
//! @return The summation of the manhattan distances.
int State_Comparator::get_total_manhattan_distances(const State& s) const
{
    int manhattan_distance_sum = 0;
    for (const auto& box_position : s.box_positions)
       manhattan_distance_sum += get_nearest_storage_distance(s, box_position);

    return manhattan_distance_sum;
}

//! @brief Get the custom heuristic value for the state.
//! @param s The state.
//! @return The heuristic value of state.
int State_Comparator::get_heuristic_value(const State& s) const
{
    return get_total_manhattan_distances(s) + get_number_of_stored_boxes(s) * -1000;
}
