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
	_xMouse = event->x();
	_yMouse = event->y();
	putToGrid();
	_xStart = _x;
	_yStart = _y;
	switch (_operation) {
		case (Operation::addIntersection): break;
		case (Operation::addBuilding): break;
		case (Operation::addCamera): break;
		case (Operation::addPedestrian): break;
		case (Operation::addStreet): break;
		case (Operation::addCar): break;
		case (Operation::addTruck): break;
		case (Operation::toggleParking): break;
		case (Operation::DELETE): break;
		case (Operation::nothing): break;
		default:
			break;
	}
	update();
}

void CityScene::mouseReleaseEvent(QMouseEvent * event) {
	isDrawing = false;
	switch (_operation) {
		case (Operation::addIntersection): 
			//if(_xStart == _x &&
			//	_yStart == _y)
			//	CityController::getInstance()->
				break;
		case (Operation::addBuilding): break;
		case (Operation::addCamera): break;
		case (Operation::addPedestrian): break;
		case (Operation::addStreet): 
			CityController::getInstance()->addStreet(Position(_xStart, _yStart), Position(_x, _y));
			break;
		case (Operation::addCar): break;
		case (Operation::addTruck): break;
		case (Operation::toggleParking): break;
		case (Operation::DELETE): break;
		case (Operation::nothing): break;
		default:
			break;
	}
	update();
}

void CityScene::mouseMoveEvent(QMouseEvent * event) {
	
	if (isDrawing) {
		_xMouse = event->x();
		_yMouse = event->y();
		if (abs(_xStart - _xMouse) > abs(_yStart - _yMouse))
			_yMouse = _yStart;
		else
			_xMouse = _xStart;
		putToGrid();
		update();
	}
}

void CityScene::paintEvent(QPaintEvent * event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QString string = QString("%1, %2")
		.arg(_x)
		.arg(_y);
	QColor secondColor(240, 255, 255);
	painter.setPen(secondColor);
	painter.setBrush(secondColor);
	QFont font = painter.font();
	font.setPointSize(18);
	painter.drawText(QPoint(_xMouse + 20, _yMouse + 20), string);
	if (isDrawing) {
		QPen pen(QColor(128, 128, 128, 128));
		switch (_operation) {
			case (Operation::addIntersection): break;
			case (Operation::addBuilding): break;
			case (Operation::addCamera): break;
			case (Operation::addPedestrian): break;
			case (Operation::addStreet): 
				pen.setWidth(2 * STREET_WIDTH);
				painter.setPen(pen);
				painter.drawLine(_xStart, _yStart, _x, _y);
				break;
			case (Operation::addCar): break;
			case (Operation::addTruck): break;
			case (Operation::toggleParking): break;
			case (Operation::DELETE): break;
			case (Operation::nothing): break;
			default:
				break;
		}
	}
	paintGrid(painter);
	GraphicFab::getStreetsGraphics(painter);
	GraphicFab::getIntersectionsGraphics(painter);
	GraphicFab::getParkingGraphics(painter);
	GraphicFab::getVehiclesGraphics(painter);
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
	_x = GAP * round( _xMouse / GAP);
	_y = GAP * round( _yMouse / GAP);
}
