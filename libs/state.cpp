#include "state.h"

bool State::operator==(State& s)
{
    return is_equal(*this, s);
}

bool State::operator!=(State& s)
{
    return !(*this == s);
}

bool State::operator!=(const State& s) const
{
    return !(*this == s);
}

bool State::operator==(const State& s) const
{
   return is_equal(*this, s);
}

//! @brief Check if piece is a piece that state maintains.
//! @param piece The piece to check.
//! @return True if piece is maintain by state. False otherwise.
bool State::is_state_piece(PIECES piece)
{
    return piece == PIECES::ROBOT || piece == PIECES::BOX || piece == PIECES::STORAGE;
}

//! @brief Check if s1 is equal to s2 considering the robot position, box positions, and storage positions.
//! @param s1 State to compare.
//! @param s2 State to compare.
//! @return True if s1 == s2. False if s1 != s2.
bool State::is_equal(const State& s1, const State& s2) const
{
    if (s1.robot_position != s2.robot_position)
        return false;

    if (s1.box_positions.size() != s2.box_positions.size())
        return false;

    for (int i = 0; i < s1.box_positions.size(); ++i)
    {
        if (s1.box_positions[i] != s2.box_positions[i])
            return false;
    }

    if (s1.storage_positions.size() != s2.storage_positions.size())
        return false;

    for (int i = 0; i < s1.storage_positions.size(); ++i)
    {
        if (s1.storage_positions[i] != s2.storage_positions[i])
            return false;
    }

    return true;
}

//! @brief Write the state to the output stream.
//! @param out The output stream.
//! @param s The state.
//! @return The modified output stream.
std::ostream& operator<<(std::ostream& out, const State& s)
{
    out << "robot_position: " << s.robot_position << ' ';
    for (const auto& box_position : s.box_positions)
        out << "box_position: " << box_position << ' ';
    for (const auto& storage_position : s.storage_positions)
        out << "storage_position: " << storage_position << ' ';

    return out;
}
