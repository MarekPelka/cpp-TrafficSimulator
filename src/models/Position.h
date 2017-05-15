#ifndef POSITION_H
#define POSITION_H
#include <utility>

class Position {
public:
    Position();
    Position(int posx, int posy);
    int x;
    int y;
    std::pair <int, int> getCoordinates();
    bool operator==(const Position &p) { return x == p.x && y == p.y; }
};
#endif