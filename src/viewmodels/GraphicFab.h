#pragma once
#include <QGraphicsItem>
#include <QRect>
#include <QPen>
#include <list>
#include <string>
#include "CityController.h"
#include "VehicleController.h"
class GraphicFab {
public:
	static std::list<QGraphicsItem*> getIntersectionsGraphics(CityController * cityCon);
	static std::list<QGraphicsItem*> getStreetsGraphics(CityController * cityCon);
	static std::list<QGraphicsRectItem*> getVehiclesGraphics(VehicleController *vehCon);
private:
	GraphicFab() {};
};