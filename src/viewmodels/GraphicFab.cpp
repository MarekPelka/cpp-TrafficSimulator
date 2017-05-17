#include "GraphicFab.h"

std::list<QGraphicsItem*> GraphicFab::getStreetsGraphics(CityController * cityCon) {
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
    std::list<QGraphicsItem*> out = {};
    int sX, sY, eX, eY;
    for (PStreet s : cityCon->getStreets()) {
        sX = s->getStartEndPositions().first.x;
        sY = s->getStartEndPositions().first.y;
        eX = s->getStartEndPositions().second.x;
        eY = s->getStartEndPositions().second.y;
        QGraphicsLineItem *line = new QGraphicsLineItem(sX, sY, eX, eY);

        QPen pen(Qt::DashLine);
        pen.setColor(Qt::white);
        line->setPen(pen);

        QGraphicsRectItem *street = nullptr;
        QGraphicsRectItem *sidewalk = nullptr;
        if (s->getDirection() == N) {
            street = new QGraphicsRectItem(eX, eY, STREET_WIDTH, abs(sY - eY));
            if (s->hasSidewalk()) {
                sidewalk = new QGraphicsRectItem(eX + STREET_WIDTH, eY, SIDEWALK_WIDTH, abs(sY - eY));
            }
        }
        else if (s->getDirection() == E) {
            street = new QGraphicsRectItem(sX, sY, abs(sX - eX), STREET_WIDTH);
            if (s->hasSidewalk()) {
                sidewalk = new QGraphicsRectItem(sX, sY + STREET_WIDTH, abs(sX - eX), SIDEWALK_WIDTH);
            }
        }
        else if (s->getDirection() == S) {
            street = new QGraphicsRectItem(sX - STREET_WIDTH, sY, STREET_WIDTH, abs(sY - eY));
            if (s->hasSidewalk()) {
                sidewalk = new QGraphicsRectItem(sX - (STREET_WIDTH + SIDEWALK_WIDTH), sY, SIDEWALK_WIDTH, abs(sY - eY));
            }
        }
        else if (s->getDirection() == W) {
            street = new QGraphicsRectItem(eX, eY - STREET_WIDTH, abs(sX - eX), STREET_WIDTH);
            if (s->hasSidewalk()) {
                sidewalk = new QGraphicsRectItem(eX, eY - (STREET_WIDTH + SIDEWALK_WIDTH), abs(sX - eX), SIDEWALK_WIDTH);
            }
        }
        if (street) {
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::darkGray);
            street->setPen(pen);
            street->setBrush(QBrush(Qt::darkGray));
            out.push_back(street);
            out.push_back(line);
            if (sidewalk) {
                pen.setStyle(Qt::SolidLine);
                pen.setColor(Qt::gray);
                sidewalk->setPen(pen);
                sidewalk->setBrush(QBrush(Qt::gray,Qt::Dense2Pattern));
                out.push_back(sidewalk);
            }
        }
    }
    return out;
}

std::list<QGraphicsItem*> GraphicFab::getIntersectionsGraphics(CityController * cityCon) {
    std::list<QGraphicsItem*> out = {};
    int X, Y;
    for (PNode n : cityCon->getNodes()) {
        X = n->getPosition().x;
        Y = n->getPosition().y;

        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::gray);
        QGraphicsRectItem *rect = new QGraphicsRectItem(X - FULL_STREET_WIDTH, Y - FULL_STREET_WIDTH, FULL_STREET_WIDTH * 2, FULL_STREET_WIDTH * 2);
        rect->setBrush(QBrush(Qt::gray));
        rect->setPen(pen);

        out.push_back(rect);

        pen.setStyle(Qt::DashLine);
        pen.setColor(Qt::white);
        QGraphicsLineItem *line = new QGraphicsLineItem(X - FULL_STREET_WIDTH, Y - FULL_STREET_WIDTH, X, Y - FULL_STREET_WIDTH);
        line->setPen(pen);
        out.push_back(line);
        line = new QGraphicsLineItem(X + FULL_STREET_WIDTH, Y - FULL_STREET_WIDTH, X + FULL_STREET_WIDTH, Y);
        line->setPen(pen);
        out.push_back(line);
        line = new QGraphicsLineItem(X, Y + FULL_STREET_WIDTH, X + FULL_STREET_WIDTH, Y + FULL_STREET_WIDTH);
        line->setPen(pen);
        out.push_back(line);
        line = new QGraphicsLineItem(X - FULL_STREET_WIDTH, Y, X - FULL_STREET_WIDTH, Y + FULL_STREET_WIDTH);
        line->setPen(pen);
        out.push_back(line);
    }
    return out;
}

std::list<QGraphicsItem*> GraphicFab::getParkingGraphics(CityController * cityCon) {
    std::list<QGraphicsItem*> out = {};
    int X, Y;
    for (PNode n : cityCon->getParkings()) {
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
        }
        else if (v.getType() == TRUCK) {
            length = TRUCK_LENGTH;
        }
        if (v.getOrientation() == N) {
            out.push_back(new QGraphicsRectItem(v.getPosition().x + VECH_OFFSET / 2, v.getPosition().y, STREET_WIDTH - VECH_OFFSET, length));
        }
        else if (v.getOrientation() == E) {
            out.push_back(new QGraphicsRectItem(v.getPosition().x - length, v.getPosition().y + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET));
        }
        else if (v.getOrientation() == S) {
            out.push_back(new QGraphicsRectItem(v.getPosition().x - STREET_WIDTH + VECH_OFFSET / 2, v.getPosition().y - length, STREET_WIDTH - VECH_OFFSET, length));
        }
        else if (v.getOrientation() == W) {
            out.push_back(new QGraphicsRectItem(v.getPosition().x, v.getPosition().y - STREET_WIDTH + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET));
        }
    }
    return out;
}

std::list<QGraphicsEllipseItem*> GraphicFab::getPedestriansGraphics(VehicleController * vehC)
{
    std::list<QGraphicsEllipseItem*> out = {};
    int X, Y;
    for (auto p : vehC->getPedestrians()) {
        X = p.getPosition().x;
        Y = p.getPosition().y;

        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::black);
        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(X, Y, PEDESTRIAN_SIZE, PEDESTRIAN_SIZE);
        ellipse->setBrush(QBrush(Qt::white));
        ellipse->setPen(pen);
        out.push_back(ellipse);
    }
    return out;
}