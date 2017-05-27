/**
* \class Position
* \ingroup models
* \details class defines a point in the plane using integer precision
* \author Michal Krzeminski
*/

#ifndef POSITION_H
#define POSITION_H
#include <utility>

class Position {
public:
    ///default constructor
    Position();
    /**constructor with parameters
    * \param x x coordinate
    * \param y y coordinate
    */
    Position(int posx, int posy);
    //// x coordinate
    int x;
    /// y coordinate
    int y;
    /** get point coordinates
    * \return pair of coordinates
    */
    std::pair <int, int> getCoordinates();
    /// equal to operator
    bool operator==(const Position &p) { return x == p.x && y == p.y; }
};
#endif