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

	CityController *cityC = CityController::getInstance();
	VehicleController *vehC = VehicleController::getInstance();
	vehC->setMainWindow(this);

	sigUpdatePositions.connect(boost::bind(&VehicleController::updatePositions, vehC, _1));

	//timer for vehicle movement
	timerId = startTimer(1000 / FPS);

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
	scene = new QGraphicsScene(ui->graphicsView);
	scene->setBackgroundBrush(Qt::darkGreen);
	ui->graphicsView->setScene(scene);

	//for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC))
	//{
	//	scene->addItem(g);
	//}

	//TESTING VEHICLES
    Node n0(p4);
    Node n1(p1);
    Node n2(p2);
    Node n3(p3);
    std::list<Node> nodes = {n0,n1,n2,n3,n0,n1,n2,n3,n0,n1,n2,n3,n0,n1,n2,n3,n0,n1,n2,n3};
	Vehicle car(CAR, nodes);
    nodes.pop_front();
    Vehicle truck(TRUCK, nodes);

    vehC->addVehicle(car);
	vehC->addVehicle(truck);
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
    scene->clear();
    //for (QRect* g : vehicleGraphics)
    for(Vehicle veh : vehC->getVehicles())
    {
        QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
        int r = veh.color.front();
        veh.color.pop_front();
        int g = veh.color.front();
        veh.color.pop_front();
        int b = veh.color.front();
        veh.color.pop_front();
        QBrush brush = QBrush(QColor(r,g,b));
        scene->addRect(*vehicleGraphics.front(), pen, brush);
        vehicleGraphics.pop_front();
    }    
    paintStreets();
}

void MainWindow::paintStreets()
{
    CityController *cityC = CityController::getInstance();
    for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC))
    {
        scene->addItem(g);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
	sigUpdatePositions(int(1000/FPS));
}