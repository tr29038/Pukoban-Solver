#include "state_hash.h"

#include <sstream>

//! @brief Create a hash for the state.
//! @param s The state to hash.
//! @return A hash of the provided state.
std::size_t State_Hash::operator()(const State& s) const
{
    std::hash<std::string> hasher;
    std::string hash;
    for (const auto& box_position : s.box_positions)
    {
        std::stringstream ss;
        ss << box_position;
        hash.append(ss.str());
    }
    std::stringstream ss;
    ss << s.robot_position;
    hash.append(ss.str());
    return hasher(hash);
}
