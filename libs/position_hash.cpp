#include "position_hash.h"

#include <sstream>

//! @brief Create a hash for the position.
//! @param p The position to hash.
//! @return The hash of the position.
std::size_t Position_Hash::operator()(Position p) const
{
    std::hash<std::string> hasher;
    std::string hash;
    std::stringstream ss;
    ss << p;
    hash.append(ss.str());
    return hasher(hash);
}
