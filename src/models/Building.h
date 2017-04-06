#pragma once
#include "src/Enums.h"
#include "src/models/Position.h"

class Building
{
public:
    Building();
    Building(Position position);
    Position position;
    int size = BUILDING_SIZE;
};
