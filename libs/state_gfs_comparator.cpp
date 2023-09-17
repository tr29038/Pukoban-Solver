#include "state_gfs_comparator.h"

bool State_Gfs_Comparator::operator()(const State& s1, const State& s2) const
{
    return is_greater_than(s1, s2);
}

//! @brief Check if s1 is greater than s2 using the sum of manhattan distances.
//! @param s1 State to compare.
//! @param s2 State to compare.
//! @return True if s1 > s2. False if s1 <= s2.
bool State_Gfs_Comparator::is_greater_than(const State& s1, const State& s2) const
{
    int f1 = get_total_manhattan_distances(s1);
    int f2 = get_total_manhattan_distances(s2);

    return f1 > f2;
}

//! @brief Check if s1 is less than s2 using the sum of manhattan distances.
//! @param s1 State to compare.
//! @param s2 State to compare.
//! @return True if s1 < s2. False if s1 >= s2.
bool State_Gfs_Comparator::is_less_than(const State& s1, const State& s2) const
{
    int f1 = get_total_manhattan_distances(s1);
    int f2 = get_total_manhattan_distances(s2);

    return f1 < f2;
}
