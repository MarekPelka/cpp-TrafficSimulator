#pragma once

#include <list>
#include <QGraphicsItem>
#include "CityController.h"
class GraphicFab
{
public:
	static std::list<QGraphicsItem*> getStreetsGraphics(CityController * cityCon);
private:
	GraphicFab() {};
};
