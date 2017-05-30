/**
* \class GraphicFab
* \ingroup viewmodels
* \details class creating qt graphical objects used in rendering views
* \author Micha³ Krzemiñski
* \author Marek Pelka
*/

#ifndef GRAPHICFAB_H
#define GRAPHICFAB_H
#include <QGraphicsItem>
#include <QRect>
#include <QPen>
#include <list>
#include <string>
#include "CityController.h"
#include "MovementController.h"
class GraphicFab {
public:
    /**generate graphics for intersections
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static std::list<QGraphicsItem*> getIntersectionsGraphics(CityController * cityCon);
    /**generate graphics for parkings
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static std::list<QGraphicsItem*> getParkingGraphics(CityController * cityCon);
    /**generate graphics for streets
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static std::list<QGraphicsItem*> getStreetsGraphics(CityController * cityCon);
    /**generate graphics for vehicles
    * \param moveCon moving objects controller
    * \return QGraphicsRectItem* list
    */
    static std::list<QGraphicsRectItem*> getVehiclesGraphics(MovementController *moveCon);
    /**generate graphics for pedestrians
    * \param moveCon moving objects controller
    * \return QGraphicsEllipseItem* list
    */
    static std::list<QGraphicsEllipseItem*> getPedestriansGraphics(MovementController *moveCon);
private:
    ///default constructor
    GraphicFab() {};
};
#endif