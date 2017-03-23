#include "GraphicFab.h"
static int QtColours[] = {0x0000FF,0x00FF00,0xFF0000,0x00FFFF,0xFF00FF,0xFFFF00};
static int start = 0;

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
		QGraphicsLineItem *line = new QGraphicsLineItem(sX - s->getDirection(), sY, eX - s->getDirection(), eY);
		QGraphicsTextItem *text = new QGraphicsTextItem;
		
		QPen pen(Qt::DashLine);
		QColor Color;
		Color.setRgb(QtColours[start]);
		pen.setColor(Color);
		line->setPen(pen);
		start++;
		if (start == sizeof(QtColours)/sizeof(int)) {
			start = 0;
		}
		//p.addText(s->getStartEndPositions().first.x + 10 * s->getDirection(), s->getStartEndPositions().first.y + 10, font, "D: " + s->getDirection());
		text->setPos(s->getStartEndPositions().first.x / 2 + s->getStartEndPositions().second.x / 2, s->getStartEndPositions().first.y - 30 - 30 * s->getDirection());
		QString str = "D: ";
		int d = s->getDirection();
		std::string stdstr = std::to_string(d);
		
		str.append(QString::fromUtf8(stdstr.c_str()));
		text->setPlainText(str);
		text->setDefaultTextColor(Color);
		out.push_back(text);
		out.push_back(line);
		/*QGraphicsRectItem *rect = new QGraphicsRectItem(sX, sY, STREET_WIDTH, sY - eY > 0 ? sY : eY);
		rect->*/
	}
	return out;
}

std::list<QRect*> GraphicFab::getVehiclesGraphics(VehicleController * vehCon)
{
	std::list<QRect*> out = {};
	for (Vehicle v : vehCon->getVehicles())
	{
		out.push_back(new QRect(v.getPosition().x, v.getPosition().y, CAR_LENGTH, STREET_WIDTH));
	}
	return out;
}
