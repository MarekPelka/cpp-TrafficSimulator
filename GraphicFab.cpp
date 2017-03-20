#include "GraphicFab.h"

std::list<QGraphicsItem*> GraphicFab::getStreetsGraphics(CityController * cityCon)
{
	std::list<QGraphicsItem*> out = {};
	int sX, sY, eX, eY;
	for (Street* s : cityCon->getStreets())
	{
		sX = s->getStartEndPositions().first.x;
		sY = s->getStartEndPositions().first.y;
		eX = s->getStartEndPositions().second.x;
		eY = s->getStartEndPositions().second.y;
		//TODO: Remove poiters
		QGraphicsLineItem *line = new QGraphicsLineItem(sX, sY, eX, eY);
		QPen pen(Qt::DashLine);
		pen.setColor(Qt::white);
		line->setPen(pen);
		out.push_back(line);
		/*QGraphicsRectItem *rect = new QGraphicsRectItem(sX, sY, STREET_WIDTH, sY - eY > 0 ? sY : eY);
		rect->*/
	}
	return out;
}
