#pragma once

#include <list>
#include <QGraphicsItem>
#include <QPen>
#include <string> 
#include "CityController.h"
class GraphicFab
{
public:
	static std::list<QGraphicsItem*> getStreetsGraphics(CityController * cityCon);
private:
	GraphicFab() {};
};
