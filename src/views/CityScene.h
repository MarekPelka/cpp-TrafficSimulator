#pragma once
#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include "../Enums.h"
#include "../viewmodels/GraphicFab.h"

class CityScene : public QWidget { //public QGraphicsScene, 
	Q_OBJECT
public:
	enum class Operation { addIntersection, 
	addBuilding, addCamera, addPedestrian, addStreet, addCar, addTruck, toggleParking, DELETE, nothing
	};

	explicit CityScene(QWidget *parent = 0);
	~CityScene();

	void setOperation(Operation o);

	void mousePressEvent(QMouseEvent * event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
	void mouseMoveEvent(QMouseEvent * event) override;
	void paintEvent(QPaintEvent * event) override;
	void keyPressEvent(QKeyEvent * event) override;

	void refresh();
    //label with info about current state of insert
    QLabel *infoLabel;
private:
	void paintGrid(QPainter & painter);
	void putToGrid();
	Operation _operation = Operation::nothing;
	int _x, _y;
	int _xMouse, _yMouse;
	int _xStart, _yStart;
	int _xGrid, _yGrid;
	const double GAP = FULL_STREET_WIDTH * 2;
	bool isDrawing = false;
};