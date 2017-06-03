#include "CityScene.h"

CityScene::CityScene(QWidget *parent) : QWidget(parent) {

	QPalette pal(palette());
	pal.setColor(QPalette::Background, QColor(99, 216, 99));
	setAutoFillBackground(true);
	setPalette(pal);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}

CityScene::~CityScene() {}

void CityScene::setOperation(Operation o) {
	_operation = o;
}

void CityScene::mousePressEvent(QMouseEvent * event) {
	isDrawing = true;
	_xGrid = _xMouse = event->x();
	_yGrid = _yMouse = event->y();
	putToGrid();
	_xStart = _x;
	_yStart = _y;
	update();
}

void CityScene::mouseReleaseEvent(QMouseEvent * event) {
	isDrawing = false;
	auto nodes = CityController::getInstance()->nodesPath(Position(_xStart, _yStart), Position(_x, _y));
	auto node = CityController::getInstance()->findNode(Position(_x, _y));
	switch (_operation) {
		case (Operation::addIntersection):
			//if(_xStart == _x &&
			//	_yStart == _y)
			//	CityController::getInstance()->
			break;
		case (Operation::addBuilding):
			if (!CityController::getInstance()->checkIfIntersectStreet(Position(_x - FULL_STREET_WIDTH, _y - FULL_STREET_WIDTH))) {
				Building building(Position(_x - FULL_STREET_WIDTH, _y - FULL_STREET_WIDTH));
				CameraController::getInstance()->addBuilding(building);
			}
			break;
		case (Operation::addCamera): 
			CameraController::getInstance()->addCamera(Camera(Position(_xStart, _yStart), 60, Street::getPredictedDirection(Position(_xStart, _yStart), Position(_xMouse, _yMouse))));
			break;
		case (Operation::addPedestrian): break;
		case (Operation::addStreet):
			CityController::getInstance()->addStreet(Position(_xStart, _yStart), Position(_x, _y));
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
		case (Operation::DELETE): break;
		case (Operation::nothing): break;
		default:
			break;
	}
	update();
}

void CityScene::mouseMoveEvent(QMouseEvent * event) {

	if (isDrawing) {
		_xGrid = _xMouse = event->x();
		_yGrid = _yMouse = event->y();
		switch (_operation) {
			case (Operation::addCamera):
			case (Operation::addStreet):
				if (abs(_xStart - _xMouse) > abs(_yStart - _yMouse))
					_yGrid = _yStart;
				else
					_xGrid = _xStart;
				break;
			default:
				break;
		}
		putToGrid();
		update();
	}
}

void CityScene::paintEvent(QPaintEvent * event) {
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
		.arg(_x)
		.arg(_y);
	QColor secondColor(240, 255, 255);
	painter.setPen(secondColor);
	painter.setBrush(secondColor);
	QFont font = painter.font();
	font.setPointSize(18);

	if (isDrawing) {
		painter.drawText(QPoint(_xMouse + 20, _yMouse + 20), string);
		painter.drawText(QPoint(_x + 20, _y + 20), string);
		QPen pen(QColor(128, 128, 128, 128));
		QBrush brush(QColor(255, 255, 255, 128));
			int angleInDegrees = atan2(_yStart - _yMouse, _xStart - _xMouse) * 180 / M_PI;
			int alfa1 = angleInDegrees - 30;
			int alfa2 = angleInDegrees + 30;
			if (alfa1 > 180)
				alfa1 = -alfa1;
			if (alfa2 > 180)
				alfa2 = -alfa2;

			painter.setBrush(brush);
		switch (_operation) {
			case (Operation::addBuilding): break;
			case (Operation::addCamera): 

				painter.drawPie(QRect(_xStart, _yStart, _xMouse - _xStart, _yMouse - _yStart),
					alfa1 * 16, alfa2 * 16);
				break;
			case (Operation::addPedestrian):
				pen.setColor(QColor(255, 255, 0, 128));
				pen.setWidth(PEDESTRIAN_SIZE);
				painter.setPen(pen);
				painter.drawLine(_xStart, _yStart, _x, _y);
				break;
			case (Operation::addStreet):
				pen.setWidth(2 * STREET_WIDTH);
				painter.setPen(pen);
				painter.drawLine(_xStart, _yStart, _x, _y);
				break;
			case (Operation::addCar):
				pen.setColor(QColor(255, 0, 0, 128));
				pen.setWidth(STREET_WIDTH - VECH_OFFSET);
				painter.setPen(pen);
				painter.drawLine(_xStart, _yStart, _x, _y);
				break;
			case (Operation::addTruck):
				pen.setColor(QColor(255, 0, 0, 128));
				pen.setWidth(STREET_WIDTH - VECH_OFFSET);
				painter.setPen(pen);
				painter.drawLine(_xStart, _yStart, _x, _y);
				break;
			case (Operation::toggleParking): break;
			case (Operation::DELETE): break;
			case (Operation::nothing): break;
			default:
				break;
		}
	}
}

void CityScene::keyPressEvent(QKeyEvent * event) {}

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
	_x = GAP * round(_xGrid / GAP);
	_y = GAP * round(_yGrid / GAP);
}
