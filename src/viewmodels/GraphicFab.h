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
    static std::list<QGraphicsItem*> getIntersectionsGraphics(CityController * cityCon);
    static std::list<QGraphicsItem*> getParkingGraphics(CityController * cityCon);
    static std::list<QGraphicsItem*> getStreetsGraphics(CityController * cityCon);
    static std::list<QGraphicsRectItem*> getVehiclesGraphics(MovementController *moveCon);
    static std::list<QGraphicsEllipseItem*> getPedestriansGraphics(MovementController *cityCon);
private:
    GraphicFab() {};
};
#endif