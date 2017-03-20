#pragma once
#include "mainwindow.h"
#include "Position.h"
#include "Vehicle.h"
#include <list>
#include <QRect>

class VehicleController
{
public:
	VehicleController();
	VehicleController(MainWindow *mw);
	void setMainWindow(MainWindow *mw);
	void addVehicle(Vehicle *vehicle);
	std::list<Vehicle*>* getVehicles();
	std::list<QRect*> getVehiclesGraphics();
private:
	MainWindow *mainWindow;
	std::list<Vehicle*> vehicles;
};
