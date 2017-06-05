/**
* \class CityScene
* \ingroup viewmodels
* \details class controlling main board of application and user input
* \author Marek Pelka
*/

#ifndef CITYSCENE_H
#define CITYSCENE_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include "../Enums.h"
#include "../viewmodels/GraphicFab.h"

class CityScene : public QWidget { 
	Q_OBJECT
public:
	/*!
	* \brief The Operation enum.
	* \details Enum class describing what is selected.
	*/
	enum class Operation { addIntersection, 
	addBuilding, addCamera, addPedestrian, addStreet, addCar, addTruck, toggleParking, remove, nothing
	};//For future use
	///default constructor
	explicit CityScene(QWidget *parent = 0);
	///destructor
	~CityScene();
	/**Selects current operation
	* \param operation
	*/
	void setOperation(Operation o);
	/**Handler for mouse down events
	* \param QMouseEvent
	*/
	void mousePressEvent(QMouseEvent * event) override;
	/**Handler for mouse up events
	* \param QMouseEvent
	*/
	void mouseReleaseEvent(QMouseEvent * event) override;
	/**Handler for mouse move events
	* \param QMouseEvent
	*/
	void mouseMoveEvent(QMouseEvent * event) override;
	/**Handler for updating interface
	* \param QKeyEvent
	*/
	void paintEvent(QPaintEvent * event) override;
	/**Handler for keybord events
	* \param QKeyEvent
	*/
	void keyPressEvent(QKeyEvent * event) override;
	///refresh allowing other classes to update interface
	void refresh();

private:
	///Paints grid on the inteface
	void paintGrid(QPainter & painter);
	///Aligns _x and _y to grid
	void putToGrid();
	///Position snapped to cross aligned to grid
	int _x, _y;
	///Current mouse position
	int _xMouse, _yMouse;
	///Start position of drawing
	int _xStart, _yStart;
	///Position snaped to cross
	int _xGrid, _yGrid;
	///Const for spaceing between grid points 
	const double GAP = FULL_STREET_WIDTH * 2;
	///Is mouse down
	bool isDrawing = false;
	///Currently selected operation
	Operation _operation = Operation::nothing;
	///Label with currently selected operation
	QLabel *infoLabel;
};
#endif