#include "directions.h"

Directions::Directions()
{
    directions.emplace_back(1, 0);
    directions.emplace_back(0, 1);
    directions.emplace_back(-1, 0);
    directions.emplace_back(0, -1);
}
