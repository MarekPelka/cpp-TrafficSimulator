#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VehicleController.h"
#include "Position.h"
#include "Enums.h"
#include "Vehicle.h"
#include <list>
#include "CityController.h"
#include "GraphicFab.h"
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CityController *cityC = new CityController();
	VehicleController *vehC = new VehicleController();

	//TESTING FOR CITI TOPOLOGY
	Position p1(100, 100);
	Position p2(500, 100);
	Position p3(500, 500);
	Position p4(100, 500);
	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);
	cityC->addStreet(p4, p1);
	//Crossing


	Position pc3(300, 50);
	Position pc4(300, 550);
	cityC->addStreet(pc3, pc4);
	Position pc1(50, 300);
	Position pc2(550, 300);
	cityC->addStreet(pc1, pc2);
	//Painting streets
	//TODO: There is some weird auto-scaling/positioning -> understend and fix
	QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
	scene->setBackgroundBrush(Qt::darkGreen);
	ui->graphicsView->setScene(scene);

	for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC))
	{
		scene->addItem(g);
	}

	//TESTING VEHICLES
	//Vehicle car(CAR, Position(30,30));
	//Vehicle truck(TRUCK, Position (500,80));
	//vehC->addVehicle(&car);
	//vehC->addVehicle(&truck);
	//
	//QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
	//QBrush brush = QBrush(QColor(184, 36, 238));

	//for (QRect* g : vehC->getVehiclesGraphics())
	//{
	//	scene->addRect(*g, pen, brush);
	//}
}

MainWindow::~MainWindow()
{
    delete ui;
}
