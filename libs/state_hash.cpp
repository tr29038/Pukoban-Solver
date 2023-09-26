#include "state_hash.h"

#include <sstream>

//! @brief Create a hash for the state.
//! @param s The state to hash.
//! @return A hash of the provided state.
std::size_t State_Hash::operator()(const State& s) const
{
    std::hash<std::string> hasher;
    std::string hash;
    std::stringstream ss;
    for (auto box : s.box_positions)
    {
        ss << box;
        hash.append(ss.str());
        ss.str("");
    }
    for (auto storage : s.storage_positions)
    {
        std::stringstream ss;
        ss << storage;
        hash.append(ss.str());
        ss.str("");
    }
    ss << s.robot_position;
    hash.append(ss.str());
    return hasher(hash);
}
