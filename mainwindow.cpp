#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CitiController.h"
#include "VehicleController.h"
#include "Position.h"
#include "Street.h"
#include "Node.h"
#include "Enums.h"
#include "Vehicle.h"
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CitiController *citiC = new CitiController(this);
	VehicleController *vehC = new VehicleController(this);

	//TESTING FOR CITI TOPOLOGY
	Position p1(10, 10);
	Position p2(50, 50);
	Position p3(10, 50);
	citiC->addStreet(p1, p2);
	citiC->addStreet(p2, p3);
	citiC->addStreet(p3, p1);
	
	//Painting streets
	//TODO: There is some weird auto-scaling/positioning -> understend and fix
	QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
	scene->setBackgroundBrush(Qt::green);
	ui->graphicsView->setScene(scene);
	for (QGraphicsItem* g : citiC->getStreetsGraphics())
	{
		scene->addItem(g);
	}

	//TESTING VEHICLES
	Vehicle car(CAR, Position(30,30));
	Vehicle truck(TRUCK, Position (80,80));
	vehC->addVehicle(&car);
	vehC->addVehicle(&truck);
	
	QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
	QBrush brush = QBrush(QColor(184, 36, 238));

	for (QRect* g : vehC->getVehiclesGraphics())
	{
		scene->addRect(*g, pen, brush);
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}
