#include "mainwindow.h"
#include "ui_mainwindow.h"
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
	VehicleController *vehC = VehicleController::getInstance();
	vehC->setMainWindow(this);

	sigUpdatePositions.connect(boost::bind(&VehicleController::updatePositions, vehC, _1));

	//timer for vehicle movement
	timerId = startTimer(1000 / FPS);

	//TESTING FOR CITI TOPOLOGY
	Position p1(10, 10);
	Position p2(50, 50);
	Position p3(50, 50);
	Position p4(10, 50);
	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);
	cityC->addStreet(p4, p1);
	//Painting streets
	//TODO: There is some weird auto-scaling/positioning -> understend and fix
	scene = new QGraphicsScene(ui->graphicsView);
	scene->setBackgroundBrush(Qt::darkGreen);
	ui->graphicsView->setScene(scene);

	for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC))
	{
		scene->addItem(g);
	}

	//TESTING VEHICLES
	Vehicle car(CAR, Position(90,90));
	vehC->addVehicle(car);
}

MainWindow::~MainWindow()
{
	killTimer(timerId);
    delete ui;
}

void MainWindow::updateVehiclesViews()
{
	VehicleController *vehC = VehicleController::getInstance();
	std::list<QRect*> vehicleGraphics = GraphicFab::getVehiclesGraphics(vehC);
	paintVehicles(vehicleGraphics);
}

void MainWindow::paintVehicles(std::list<QRect*> vehicleGraphics)
{
	scene->clear();
	QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
	QBrush brush = QBrush(QColor(184, 36, 238));
	for (QRect* g : vehicleGraphics)
	{
		scene->addRect(*g, pen, brush);
	}
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	sigUpdatePositions(int(1000/FPS));
}