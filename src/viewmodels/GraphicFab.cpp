#include "GraphicFab.h"

void GraphicFab::getStreetsGraphics(QPainter &painter) {
    int sX, sY, eX, eY;
    for (PStreet s : CityController::getInstance()->getStreets()) {
        sX = s->getStartEndPositions().first.x;
        sY = s->getStartEndPositions().first.y;
        eX = s->getStartEndPositions().second.x;
        eY = s->getStartEndPositions().second.y;
		QPen pen(Qt::DashLine);
		pen.setColor(Qt::white);
		painter.setPen(pen);
		painter.drawLine(sX, sY, eX, eY);
		pen.setStyle(Qt::SolidLine);
		pen.setColor(Qt::darkGray);
		painter.setPen(pen);
		painter.setBrush(QBrush(Qt::darkGray));
        if (s->getDirection() == N) {
            painter.drawRect(eX, eY, STREET_WIDTH, abs(sY - eY));
            if (s->hasSidewalk()) {
				setSidewalkPainter(painter);
				painter.drawRect(eX + STREET_WIDTH, eY, SIDEWALK_WIDTH, abs(sY - eY));
            }
        }
        else if (s->getDirection() == E) {
			painter.drawRect(sX, sY, abs(sX - eX), STREET_WIDTH);
            if (s->hasSidewalk()) {
				setSidewalkPainter(painter);
				painter.drawRect(sX, sY + STREET_WIDTH, abs(sX - eX), SIDEWALK_WIDTH);
            }
        }
        else if (s->getDirection() == S) {
			painter.drawRect(sX - STREET_WIDTH, sY, STREET_WIDTH, abs(sY - eY));
            if (s->hasSidewalk()) {
				setSidewalkPainter(painter);
				painter.drawRect(sX - (STREET_WIDTH + SIDEWALK_WIDTH), sY, SIDEWALK_WIDTH, abs(sY - eY));
            }
        }
        else if (s->getDirection() == W) {
			painter.drawRect(eX, eY - STREET_WIDTH, abs(sX - eX), STREET_WIDTH);
            if (s->hasSidewalk()) {
				setSidewalkPainter(painter);
				painter.drawRect(eX, eY - (STREET_WIDTH + SIDEWALK_WIDTH), abs(sX - eX), SIDEWALK_WIDTH);
            }
        }
    }
}

void GraphicFab::getIntersectionsGraphics(QPainter &painter) {
    int X, Y;
	QPixmap m("images/inter.png");
    for (PNode n : CityController::getInstance()->getNodes()) {
		X = n->getPosition().x;
		Y = n->getPosition().y;
		painter.drawPixmap(QPoint(X - FULL_STREET_WIDTH, Y - FULL_STREET_WIDTH), QPixmap(m));	
    }
}

void GraphicFab::getParkingGraphics(QPainter &painter) {
    int X, Y;
    for (PNode n : CityController::getInstance()->getParkings()) {
        X = n->getPosition().x;
        Y = n->getPosition().y;

        QPen pen(Qt::SolidLine);
		QColor pColor(99, 99, 216);
        pen.setColor(pColor);
		painter.setPen(pen);
		painter.setBrush(QBrush(pColor));
        painter.drawRect(X - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, Y - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER);
		pen.setColor(Qt::white);
		painter.setPen(pen);
		//auto r = QString()->boundingRect();
		painter.drawText(QRect(X - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, Y - STREET_WIDTH * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER, STREET_WIDTH * 2 * PARKING_SIZE_MULTIPLIER)
			, Qt::AlignCenter, "Parking");
    }
}

void GraphicFab::getVehiclesGraphics(QPainter &painter) {
    int length = 0;
    for (PVehicle v : MovementController::getInstance()->getVehicles()) {
		
		painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
		painter.setBrush(QBrush(GraphicFab::getVehicleColor(v->getSpeed())));
        if (v->getType() == CAR) {
            length = CAR_LENGTH;
        }
        else if (v->getType() == TRUCK) {
            length = TRUCK_LENGTH;
        }
        if (v->getOrientation() == N) {
			painter.drawRect(v->getPosition().x + VECH_OFFSET / 2, v->getPosition().y, STREET_WIDTH - VECH_OFFSET, length);
        }
        else if (v->getOrientation() == E) {
			painter.drawRect(v->getPosition().x - length, v->getPosition().y + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET);
        }
        else if (v->getOrientation() == S) {
			painter.drawRect(v->getPosition().x - STREET_WIDTH + VECH_OFFSET / 2, v->getPosition().y - length, STREET_WIDTH - VECH_OFFSET, length);
        }
        else if (v->getOrientation() == W) {
			painter.drawRect(v->getPosition().x, v->getPosition().y - STREET_WIDTH + VECH_OFFSET / 2, length, STREET_WIDTH - VECH_OFFSET);
        }
    }
}

void GraphicFab::getPedestriansGraphics(QPainter &painter)
{
    int X, Y;
    for (auto p : MovementController::getInstance()->getPedestrians()) {
        X = p->getPosition().x;
        Y = p->getPosition().y;

        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::black);
		painter.setPen(pen);
		painter.setBrush(QBrush(Qt::white));
        painter.drawEllipse(X, Y, PEDESTRIAN_SIZE, PEDESTRIAN_SIZE);
    }
}

void GraphicFab::getBuildingsGraphics(QPainter &painter) {
	for (auto p : CameraController::getInstance()->getBuildings()) {
		painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
		painter.setBrush(QBrush(QColor(152, 152, 152)));
		painter.drawRect(p.position.x, p.position.y, p.size, p.size);
	}
}

void GraphicFab::getCamerasGraphics(QPainter &painter) {
	for (auto camera : CameraController::getInstance()->getCameras()) {
		QRect cam(camera.getPosition().x - CAMERA_SIZE/2, camera.getPosition().y - CAMERA_SIZE / 2, CAMERA_SIZE, CAMERA_SIZE);
		painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine));
		painter.setBrush(QBrush(QColor(255, 0, 0)));
		painter.drawEllipse(cam);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(QColor(255, 255, 255, 64)));
		QPolygon polygon;
		if (camera.getDirection() == W) //left
			polygon << QPoint(camera.getPosition().x, camera.getPosition().y)
			<< QPoint(camera.getPosition().x - sqrt(CAMERA_PRECISION) * 3 / 4, camera.getPosition().y - sqrt(CAMERA_PRECISION) * sqrt(3) / 4)
			<< QPoint(camera.getPosition().x - sqrt(CAMERA_PRECISION), camera.getPosition().y)
			<< QPoint(camera.getPosition().x - sqrt(CAMERA_PRECISION) * 3 / 4, camera.getPosition().y + sqrt(CAMERA_PRECISION) * sqrt(3) / 4);
		else if (camera.getDirection() == E) //right
			polygon << QPoint(camera.getPosition().x, camera.getPosition().y)
			<< QPoint(camera.getPosition().x + sqrt(CAMERA_PRECISION) * 3 / 4, camera.getPosition().y - sqrt(CAMERA_PRECISION) * sqrt(3) / 4)
			<< QPoint(camera.getPosition().x + sqrt(CAMERA_PRECISION), camera.getPosition().y)
			<< QPoint(camera.getPosition().x + sqrt(CAMERA_PRECISION) * 3 / 4, camera.getPosition().y + sqrt(CAMERA_PRECISION) * sqrt(3) / 4);
		else if (camera.getDirection() == S) //down
			polygon << QPoint(camera.getPosition().x, camera.getPosition().y)
			<< QPoint(camera.getPosition().x - sqrt(CAMERA_PRECISION) * sqrt(3) / 4, camera.getPosition().y + sqrt(CAMERA_PRECISION) * 3 / 4)
			<< QPoint(camera.getPosition().x, camera.getPosition().y + sqrt(CAMERA_PRECISION))
			<< QPoint(camera.getPosition().x + sqrt(CAMERA_PRECISION) * sqrt(3) / 4, camera.getPosition().y + sqrt(CAMERA_PRECISION) * 3 / 4);
		else if (camera.getDirection() == N) //up
			polygon << QPoint(camera.getPosition().x, camera.getPosition().y)
			<< QPoint(camera.getPosition().x - sqrt(CAMERA_PRECISION) * sqrt(3) / 4, camera.getPosition().y - sqrt(CAMERA_PRECISION) * 3 / 4)
			<< QPoint(camera.getPosition().x, camera.getPosition().y - sqrt(CAMERA_PRECISION))
			<< QPoint(camera.getPosition().x + sqrt(CAMERA_PRECISION) * sqrt(3) / 4, camera.getPosition().y - sqrt(CAMERA_PRECISION) * 3 / 4);
		painter.drawPolygon(polygon);
	}
}

QColor GraphicFab::getVehicleColor(double speed) {
    //rescaling
	speed *= 100;
	speed += 30;

	int r, g, b;
	double d = (max_rgb+1) / 20;

	if (speed < 0) { //ultraviolet
		r = g = b = 0;
	} else if (speed < violet) {
		r = static_cast <int> (max_rgb - d * speed);
		g = 0;
		b = max_rgb;
	} else if (speed < dark_blue) {
		r = 0;
		g = static_cast <int> (d * (speed - violet));
		b = max_rgb;
	} else if (speed < cyan) {
		r = 0;
		g = max_rgb;
		b = static_cast <int> (max_rgb - d * (speed - dark_blue));
	} else if (speed < light_green) {
		r = static_cast <int> (d * (speed - cyan));
		g = max_rgb;
		b = 0;
	} else if (speed < yellow) {
		r = max_rgb;
		g = static_cast <int> (max_rgb - d * (speed - light_green));
		b = 0;
	} else { //infrared
		r = g = b = 0;
	}
	return QColor(r, g, b);
}

void GraphicFab::setSidewalkPainter(QPainter &painter) {
	QPen pen(Qt::SolidLine);
	pen.setColor(Qt::gray);
	painter.setPen(pen);
	painter.setBrush(QBrush(Qt::gray, Qt::Dense2Pattern));
}
