#include "state_astar_comparator.h"

#include <iostream>

bool State_Astar_Comparator::operator()(const State& s1, const State& s2) const
{
    return is_less_than(s1, s2);
}

//! @brief Check if s1 is greater than s2 using the sum of manhattan distances, distance from the initial state, and the number of stored boxes.
//! @param s1 The state to check if it's greater than.
//! @param s2 The state to compare to.
//! @return True if s1 > s2. False if s1 <= s2.
bool State_Astar_Comparator::is_greater_than(const State& s1, const State& s2) const
{
    int f1 = s1.current_total_distance_from_start + get_heuristic_value(s1);
    int f2 = s2.current_total_distance_from_start + get_heuristic_value(s2);

    return f1 > f2;
}

//! @brief Check if s1 is less than s2 using the sum of manhattan distances, distance from the initial state, and the number of stored boxes.
//! @param s1 The state to check if it's less than.
//! @param s2 The state to compare to.
//! @return True if s1 < s2. False if s1 >= s2.
bool State_Astar_Comparator::is_less_than(const State& s1, const State& s2) const
{
    int f1 = s1.current_total_distance_from_start + get_heuristic_value(s1);
    int f2 = s2.current_total_distance_from_start + get_heuristic_value(s2);

    return f1 < f2;
}
