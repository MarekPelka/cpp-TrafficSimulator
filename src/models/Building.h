/**
* \class Building
* \ingroup models
* \details class representing building object
* \author Michal Krzeminski
*/

#ifndef BUILDING_H
#define BUILDING_H

#include "../Enums.h"
#include "Position.h"

class Building {
public:
    ///default constructor
    Building();
    /** constructor with parameter
    * \param position building positon
    */
    Building(Position position);
    /// equal to operator
    bool operator==(const Building &v);

    ///building position
    Position position;
    ///building size
    int size = 2 * FULL_STREET_WIDTH;
};
#endif