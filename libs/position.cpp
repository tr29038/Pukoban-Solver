#include "position.h"

//! @brief Write to the position to the output stream in the format: x,y.
//! @param output The output stream.
//! @param p The position.
//! @return The modified output stream.
std::ostream& operator<<(std::ostream& output, Position p)
{
    output << p.x << ',' << p.y;

    return output;
}
