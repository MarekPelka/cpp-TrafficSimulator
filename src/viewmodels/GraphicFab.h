/**
* \class GraphicFab
* \ingroup viewmodels
* \details class used in rendering graphical views
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
    */
    static void getIntersectionsGraphics(QPainter &painter);
    /**generate graphics for parkings
    */
    static void getParkingGraphics(QPainter &painter);
    /**generate graphics for streets
    */
    static void getStreetsGraphics(QPainter &painter);
    /**generate graphics for vehicles
    */
    static void getVehiclesGraphics(QPainter &painter);
    /**generate graphics for pedestrians
    */
    static void getPedestriansGraphics(QPainter &painter);
    /**generate graphics for buildings
    */
	static void getBuildingsGraphics(QPainter & painter);
    /**generate graphics for cameras
    */
	static void getCamerasGraphics(QPainter & painter);
    /**generate vehicle color
    */
	static QColor getVehicleColor(double speed);

private:
    ///default constructor
    GraphicFab() {};
    /**generate graphics for sidewalk
    */
	static void setSidewalkPainter(QPainter &painter);
};
#endif