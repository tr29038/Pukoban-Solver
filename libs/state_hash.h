#pragma once

#include <state.h>

#include <functional>

struct State_Hash
{
    std::size_t operator()(const State&) const;
};
