#include "Building.h"

Building::Building() {
}

Building::Building(Position pos) {
    position = pos;
}

bool Building::operator==(const Building & v) {
    return position == v.position;
}