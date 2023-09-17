#pragma once

#include <position.h>

#include <functional>

struct Position_Hash
{
    std::size_t operator()(Position) const;
};
