#include "state_comparator.h"

#include <sstream>

//! @brief Get the manhattan distance between two positions/points.
//! @param p1 One of the positions.
//! @param p2 One of the positions.
//! @return The manhattan distance between the two positions.
int State_Comparator::get_manhattan_distance(Position p1, Position p2) const
{
   return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

//! @brief Get the manhattan distance from the robot to the box nearest to it.
//! @param s The state in consideration.
//! @return The manhattan distance from the robot to the box nearest to it.
int State_Comparator::get_robot_to_nearest_box_distance(const State& s) const
{
    int shortest_distance = INT_MAX;
    for (auto box_position : s.box_positions)
    {
        auto distance = get_manhattan_distance(s.robot_position, box_position);
        shortest_distance = distance < shortest_distance ? distance : shortest_distance;
    }

    return shortest_distance;
}

//! @brief Get a sorted list of all box and storage pairs with the corresponding manhattan distance.
//! @param s The state in consideration.
//! @return A sorted list (shortest distance first) of all box and storage pairs with the corresponding manhattan distance between the two.
std::list<std::tuple<std::string, std::string, int>> State_Comparator::get_distances(const State& s) const
{
    std::list<std::tuple<std::string, std::string, int>> box_storage_distances;
    std::stringstream ss;
    for (auto box_position : s.box_positions)
    {
        ss.str("");
        ss << box_position;
        std::string box_str = ss.str();
        for (auto storage_position : s.storage_positions)
        {
            ss.str("");
            ss << storage_position;
            std::string storage_str = ss.str();

            auto distance = get_manhattan_distance(box_position, storage_position);

            box_storage_distances.emplace(box_storage_distances.begin(), box_str, storage_str, distance);
	}
    }

    box_storage_distances.sort([](const std::tuple<std::string, std::string, int>& element1, const std::tuple<std::string, std::string, int>& element2)
    {
        return std::get<2>(element1) < std::get<2>(element2);
    });

    return box_storage_distances;
}

//! @brief Get the custom heuristic value for the state.
//!        Shortest distance pairs between a box and storage (omitting duplicates) + the distance from the robot to the
//!        storage nearest to it.
//! @param s The state.
//! @return The heuristic value of state.
int State_Comparator::get_heuristic_value(const State& s) const
{
    auto box_storage_distances = get_distances(s);
    std::unordered_set<std::string> marked_boxes, marked_storages;
    int heuristic_value = get_robot_to_nearest_box_distance(s);;
    for (const auto& [box, storage, distance] : box_storage_distances)
    {
        // Don't account for any single box more than once.
        if (std::find(marked_boxes.begin(), marked_boxes.end(), box) != marked_boxes.end())
            continue;

        // Don't account for any single storage more than once.
        if (std::find(marked_storages.begin(), marked_storages.end(), storage) != marked_storages.end())
            continue;

        heuristic_value += distance;

        // Mark box and storage to ensure no duplicate considerations.
        marked_boxes.insert(box);
        marked_storages.insert(storage);
    }

    return heuristic_value;
}
