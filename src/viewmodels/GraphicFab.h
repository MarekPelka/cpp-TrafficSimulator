/**
* \class GraphicFab
* \ingroup viewmodels
* \details class creating qt graphical objects used in rendering views
* \author Micha³ Krzemiñski
* \author Marek Pelka
*/

#ifndef GRAPHICFAB_H
#define GRAPHICFAB_H
#include <QPainter>
#include <list>
#include <string>
#include "CityController.h"
#include "MovementController.h"
#include "CameraController.h"
class GraphicFab {
public:
    /**generate graphics for intersections
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static void getIntersectionsGraphics(QPainter &painter);
    /**generate graphics for parkings
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static void getParkingGraphics(QPainter &painter);
    /**generate graphics for streets
    * \param cityCon city controller
    * \return QGraphicsItem* list
    */
    static void getStreetsGraphics(QPainter &painter);
    /**generate graphics for vehicles
    * \param moveCon moving objects controller
    * \return QGraphicsRectItem* list
    */
    static void getVehiclesGraphics(QPainter &painter);
    /**generate graphics for pedestrians
    * \param moveCon moving objects controller
    * \return QGraphicsEllipseItem* list
    */
    static void getPedestriansGraphics(QPainter &painter);

	static void getBuildingsGraphics(QPainter & painter);

	static void getCamerasGraphics(QPainter & painter);

	static QColor getVehicleColor(double speed);

private:
    ///default constructor
    GraphicFab() {};
	
	static void setSidewalkPainter(QPainter &painter);
};
#endif