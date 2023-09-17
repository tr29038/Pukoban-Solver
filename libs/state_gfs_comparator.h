#pragma once

#include "state_comparator.h"

class State_Gfs_Comparator : public State_Comparator
{
    public:
        bool operator()(const State&, const State&) const override;

        bool is_greater_than(const State&, const State&) const override;
        bool is_less_than(const State&, const State&) const override;
};
