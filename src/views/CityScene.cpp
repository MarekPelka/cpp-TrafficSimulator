#include "CityScene.h"

CityScene::CityScene(QWidget *parent) : QWidget(parent) {

	QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(99, 216, 99));
	setAutoFillBackground(true);
	setPalette(pal);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

    infoLabel = new QLabel(" ", this);
    infoLabel->setAlignment(Qt::AlignBottom);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setStyleSheet("QLabel { color : white; }");
    infoLabel->setGeometry(QRect(20, 20, 80, LABEL_HEIGHT));
}

CityScene::~CityScene() {}

void CityScene::setOperation(Operation o) {
	operation = o;
    switch (o) {
        case (Operation::addBuilding):
            infoLabel->setText("Budynek");
            break;
        case (Operation::addCamera):
            infoLabel->setText("Kamera");
            break;
        case (Operation::addPedestrian):
            infoLabel->setText("Pieszy");
            break;
        case (Operation::addCar):
            infoLabel->setText(QStringLiteral("Samochód"));
            break;
        case (Operation::addTruck):
            infoLabel->setText(QStringLiteral("Ciê¿arówka"));
            break;
        case (Operation::addStreet):
            infoLabel->setText("Ulica");
            break;
		case (Operation::remove):
			infoLabel->setText("Usuwanie!");
			break;
        case (Operation::toggleParking):
            infoLabel->setText("Parking");
            break;
		default:
			infoLabel->setText("");
			break;
    }
}

void CityScene::mousePressEvent(QMouseEvent * event) {
	if (event->button() == Qt::RightButton) {
		operation = Operation::nothing;
		infoLabel->setText("");
	}
		
	isDrawing = true;
	xGrid = xMouse = event->x();
	yGrid = yMouse = event->y();
	putToGrid();
	xStart = x;
	yStart = y;
	update();
}

void CityScene::mouseReleaseEvent(QMouseEvent * event) {
	isDrawing = false;
	auto nodes = CityController::getInstance()->nodesPath(Position(xStart, yStart), Position(x, y));
	auto node = CityController::getInstance()->findNode(Position(x, y));
	switch (operation) {
		case (Operation::addIntersection):
			break;
		case (Operation::addBuilding):
			if (!CityController::getInstance()->checkIfIntersectStreet(Position(x - FULL_STREET_WIDTH, y - FULL_STREET_WIDTH))) {
				Building building(Position(x - FULL_STREET_WIDTH, y - FULL_STREET_WIDTH));
				CameraController::getInstance()->addBuilding(building);
			}
			break;
		case (Operation::addCamera): 
			CameraController::getInstance()->addCamera(Camera(Position(xStart, yStart), 60, Street::getPredictedDirection(Position(xStart, yStart), Position(xGrid, yGrid))));
			break;
		case (Operation::addPedestrian): break;
		case (Operation::addStreet):
			CityController::getInstance()->addStreet(Position(xStart, yStart), Position(x, y));
			break;
		case (Operation::addCar):
			if (nodes.size() > 1) {
				Vehicle car(CAR, nodes);
				MovementController::getInstance()->addVehicle(car);
			}
			break;
		case (Operation::addTruck):
			if (nodes.size() > 1) {
				Vehicle truck(TRUCK, nodes);
				MovementController::getInstance()->addVehicle(truck);
			}
			break;
		case (Operation::toggleParking):
			if (node == PNode())
				break;
			if (node->isParking())
				CityController::getInstance()->downgradeFromParking(node);
			else
				CityController::getInstance()->upgradeToParking(node);
			break;
		case (Operation::remove): 
			xGrid = xMouse = event->x();
			yGrid = yMouse = event->y();
			putToGrid();
			CityController::getInstance()->deleteStuff(Position(x, y));
			break;
		case (Operation::nothing): break;
		default:
			break;
	}
	update();
}

void CityScene::mouseMoveEvent(QMouseEvent * event) {

	if (isDrawing) {
		xGrid = xMouse = event->x();
		yGrid = yMouse = event->y();
		switch (operation) {
			case (Operation::addCamera):
			case (Operation::addStreet):
				if (abs(xStart - xMouse) > abs(yStart - yMouse))
					yGrid = yStart;
				else
					xGrid = xStart;
				break;
			default:
				break;
		}
		putToGrid();
		update();
	}
}

void CityScene::paintEvent(QPaintEvent * event) {
	event->accept();
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	paintGrid(painter);
	GraphicFab::getStreetsGraphics(painter);
	GraphicFab::getIntersectionsGraphics(painter);
	
	GraphicFab::getBuildingsGraphics(painter);
	GraphicFab::getCamerasGraphics(painter);
	GraphicFab::getPedestriansGraphics(painter);
	GraphicFab::getVehiclesGraphics(painter);
	GraphicFab::getParkingGraphics(painter);
	
	QString string = QString("%1, %2")
		.arg(x)
		.arg(y);
	QColor secondColor(240, 255, 255);
	painter.setPen(secondColor);
	painter.setBrush(secondColor);
	QFont font = painter.font();
	font.setPointSize(18);
	QPolygon polygon;
	//QLine line(xStart, yStart, xGrid, yGrid);
	if (isDrawing) {
		painter.drawText(QPoint(xMouse + 20, yMouse + 20), string);
		painter.drawText(QPoint(x + 20, y + 20), string);
		QPen pen(QColor(128, 128, 128, 128));
		QBrush brush(QColor(255, 255, 255, 128));
		QPoint ss = QPoint(xStart, yStart);
		QPoint ee = QPoint(xGrid, yGrid);
		QLineF line = QLineF(ss, ee);
		painter.setBrush(brush);
		switch (operation) {
			case (Operation::addBuilding): break;
			case (Operation::addCamera): 
				if (xStart - xGrid < 0) //left
					polygon << ss << QPoint(xGrid - line.length() / 4, yGrid - line.length() * sqrt(3) / 4) << ee << QPoint(xGrid - line.length() / 4, yGrid + line.length() * sqrt(3) / 4);
				else if (xStart - xGrid > 0) //right
					polygon << ss << QPoint(xGrid + line.length() / 4, yGrid - line.length() * sqrt(3) / 4) << ee << QPoint(xGrid + line.length() / 4, yGrid + line.length() * sqrt(3) / 4);
				else if (yStart - yGrid < 0) //down
					polygon << ss << QPoint(xGrid - line.length() * sqrt(3) / 4, yGrid - line.length() / 4) << ee << QPoint(xGrid + line.length() * sqrt(3) / 4, yGrid - line.length() / 4);
				else if (yStart - yGrid > 0) //up
					polygon << ss << QPoint(xGrid - line.length() * sqrt(3) / 4, yGrid + line.length() / 4) << ee << QPoint(xGrid + line.length() * sqrt(3) / 4, yGrid + line.length() / 4);
				painter.drawPolygon(polygon);
				break;
			case (Operation::addPedestrian):
				pen.setColor(QColor(255, 255, 0, 128));
				pen.setWidth(PEDESTRIAN_SIZE);
				painter.setPen(pen);
				painter.drawLine(xStart, yStart, x, y);
				break;
			case (Operation::addStreet):
				pen.setWidth(2 * STREET_WIDTH);
				painter.setPen(pen);
				painter.drawLine(xStart, yStart, x, y);
				break;
			case (Operation::addCar):
				pen.setColor(QColor(255, 0, 0, 128));
				pen.setWidth(STREET_WIDTH - VECH_OFFSET);
				painter.setPen(pen);
				painter.drawLine(xStart, yStart, x, y);
				break;
			case (Operation::addTruck):
				pen.setColor(QColor(255, 0, 0, 128));
				pen.setWidth(STREET_WIDTH - VECH_OFFSET);
				painter.setPen(pen);
				painter.drawLine(xStart, yStart, x, y);
				break;
			case (Operation::toggleParking): break;
			case (Operation::remove): break;
			case (Operation::nothing): break;
			default:
				break;
		}
	}
}

void CityScene::refresh() {
	update();
}

void CityScene::paintGrid(QPainter &painter) {
	painter.setPen(QColor(0, 0, 0));
	for (int x = 0; x < this->width();
		x += GAP) {
		for (int y = 0; y < this->height();
			y += GAP) {
			painter.drawPoint(x, y);;
		}
	}
}

void CityScene::putToGrid() {
	x = GAP * round(xGrid / GAP);
	y = GAP * round(yGrid / GAP);
}
