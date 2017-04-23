#include "GraphicFab.h"

std::list<QGraphicsItem*> GraphicFab::getStreetsGraphics(CityController * cityCon) {
	std::list<QGraphicsItem*> out = {};
	int sX, sY, eX, eY;
	for (Street* s : cityCon->getStreets()) {
		sX = s->getStartEndPositions().first.x;
		sY = s->getStartEndPositions().first.y;
		eX = s->getStartEndPositions().second.x;
		eY = s->getStartEndPositions().second.y;
		//TODO: Remove poiters?
		QGraphicsLineItem *line = new QGraphicsLineItem(sX, sY, eX, eY);

		QPen pen(Qt::DashLine);
		pen.setColor(Qt::white);
		line->setPen(pen);
		//HOW TO DRAW TEXT:
		//p.addText(s->getStartEndPositions().first.x + 10 * s->getDirection(), s->getStartEndPositions().first.y + 10, font, "D: " + s->getDirection());
		//text->setPos(s->getStartEndPositions().first.x / 2 + s->getStartEndPositions().second.x / 2, s->getStartEndPositions().first.y - 30 - 30 * s->getDirection());
		//QString str = "D: ";
		//int d = s->getDirection();
		//std::string stdstr = std::to_string(d);

		//str.append(QString::fromUtf8(stdstr.c_str()));
		//text->setPlainText(str);
		//text->setDefaultTextColor(Color);
		//out.push_back(text);
		QGraphicsRectItem *rect = nullptr;
		if (s->getDirection() == N) {
			rect = new QGraphicsRectItem(eX, eY, STREET_WIDTH, abs(sY - eY));
		} else if (s->getDirection() == E) {
			rect = new QGraphicsRectItem(sX, sY, abs(sX - eX), STREET_WIDTH);
		} else if (s->getDirection() == S) {
			rect = new QGraphicsRectItem(sX - STREET_WIDTH, sY, STREET_WIDTH, abs(sY - eY));
		} else if (s->getDirection() == W) {
			rect = new QGraphicsRectItem(eX, eY - STREET_WIDTH, abs(sX - eX), STREET_WIDTH);
		}
        if (rect) {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::gray);
            rect->setPen(pen);
            rect->setBrush(QBrush(Qt::gray));
            out.push_back(rect);
            out.push_back(line);
        }
	}
	return out;
}

std::list<QGraphicsItem*> GraphicFab::getIntersectionsGraphics(CityController * cityCon) {
	std::list<QGraphicsItem*> out = {};
	int X, Y;
	for (Node* n : cityCon->getNodes()) {
		X = n->getPosition().x;
		Y = n->getPosition().y;

		QPen pen(Qt::SolidLine);
		pen.setColor(Qt::gray);
		QGraphicsRectItem *rect = new QGraphicsRectItem(X - STREET_WIDTH, Y - STREET_WIDTH, STREET_WIDTH * 2, STREET_WIDTH * 2);
		rect->setBrush(QBrush(Qt::gray));
		rect->setPen(pen);

		out.push_back(rect);

		pen.setStyle(Qt::DashLine);
		pen.setColor(Qt::white);
		QGraphicsLineItem *line = new QGraphicsLineItem(X - STREET_WIDTH, Y - STREET_WIDTH, X, Y - STREET_WIDTH);
		line->setPen(pen);
		out.push_back(line);
		line = new QGraphicsLineItem(X + STREET_WIDTH, Y - STREET_WIDTH, X + STREET_WIDTH, Y);
		line->setPen(pen);
		out.push_back(line);
		line = new QGraphicsLineItem(X, Y + STREET_WIDTH, X + STREET_WIDTH, Y + STREET_WIDTH);
		line->setPen(pen);
		out.push_back(line);
		line = new QGraphicsLineItem(X - STREET_WIDTH, Y, X - STREET_WIDTH, Y + STREET_WIDTH);
		line->setPen(pen);
		out.push_back(line);
	}
	return out;
}

std::list<QGraphicsItem*> GraphicFab::getParkingGraphics(CityController * cityCon)
{
	std::list<QGraphicsItem*> out = {};
	int X, Y;
	for (Node* n : cityCon->getParkings()) {
		X = n->getPosition().x;
		Y = n->getPosition().y;

		QPen pen(Qt::SolidLine);
		pen.setColor(Qt::black);
		QGraphicsRectItem *rect = new QGraphicsRectItem(X - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, Y - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER);
		rect->setBrush(QBrush(Qt::black));
		rect->setPen(pen);

		out.push_back(rect);
	}
	return out;
}

std::list<QGraphicsRectItem*> GraphicFab::getVehiclesGraphics(VehicleController * vehCon) {
	std::list<QGraphicsRectItem*> out = {};
	int length = 0;
	for (Vehicle v : vehCon->getVehicles()) {
		if (v.getType() == CAR) {
			length = CAR_LENGTH;
		} else if (v.getType() == TRUCK) {
			length = TRUCK_LENGTH;
		}
		if (v.getOrientation() == N) {
			out.push_back(new QGraphicsRectItem(v.getPosition().x + VECH_OFFSET / 2, v.getPosition().y, STREET_WIDTH - VECH_OFFSET, length));
		} else if (v.getOrientation() == E) {
			out.push_back(new QGraphicsRectItem(v.getPosition().x - length, v.getPosition().y + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET));
		} else if (v.getOrientation() == S) {
			out.push_back(new QGraphicsRectItem(v.getPosition().x - STREET_WIDTH + VECH_OFFSET / 2, v.getPosition().y - length, STREET_WIDTH - VECH_OFFSET, length));
		} else if (v.getOrientation() == W) {
			out.push_back(new QGraphicsRectItem(v.getPosition().x, v.getPosition().y - STREET_WIDTH + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET));
		}
	}
	return out;
}
