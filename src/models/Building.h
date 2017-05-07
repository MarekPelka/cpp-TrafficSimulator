#pragma once
#include "../Enums.h"
#include "Position.h"

class Building {
public:
    Building();
    Building(Position position);
    bool operator==(const Building &v);

    Position position;
    int size = BUILDING_SIZE;
};
