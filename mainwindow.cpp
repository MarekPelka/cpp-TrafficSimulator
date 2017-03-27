#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Position.h"
#include "Enums.h"
#include "Vehicle.h"
#include <list>
#include "CityController.h"
#include "GraphicFab.h"
#include <QGraphicsItem>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

    //dropdown menu
    createActions();
    createMenus();

    //initialize controllers
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

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
	cityC->addStreet(p1, p4);
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

	streetGroup = new QGraphicsItemGroup();
	nodeGroup = new QGraphicsItemGroup();
	vechicleGroup = new QGraphicsItemGroup();

	scene->addItem(streetGroup);
	scene->addItem(nodeGroup);
	scene->addItem(vechicleGroup);

	paintStreets();
	paintIntersections();

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

MainWindow::~MainWindow() {
	killTimer(timerId);
	delete ui;
}

void MainWindow::updateVehiclesViews() {

	VehicleController *vehC = VehicleController::getInstance();
	std::list<QGraphicsRectItem*> vehicleGraphics = GraphicFab::getVehiclesGraphics(vehC);
	scene->removeItem(vechicleGroup);
	delete vechicleGroup;
	vechicleGroup = new QGraphicsItemGroup();
	for (Vehicle veh : vehC->getVehicles()) {
		QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
		int r = veh.color.front();
		veh.color.pop_front();
		int g = veh.color.front();
		veh.color.pop_front();
		int b = veh.color.front();
		veh.color.pop_front();
		QBrush brush = QBrush(QColor(r, g, b));
		vehicleGraphics.front()->setBrush(brush);
		vehicleGraphics.front()->setPen(pen);
		vechicleGroup->addToGroup(vehicleGraphics.front());
		vehicleGraphics.pop_front();
	}
	scene->addItem(vechicleGroup);	
}

void MainWindow::paintStreets() {
	CityController *cityC = CityController::getInstance();
	for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC)) {
		streetGroup->addToGroup(g);
	}
}

void MainWindow::paintIntersections() {
	CityController *cityC = CityController::getInstance();
	for (QGraphicsItem* g : GraphicFab::getIntersectionsGraphics(cityC)) {
		nodeGroup->addToGroup(g);
	}
}

void MainWindow::timerEvent(QTimerEvent *event) {
	sigUpdatePositions(int(1000 / FPS));
}

void MainWindow::createActions() {
    scenario1Act = new QAction(tr("&Scenariusz 1"), this);
    connect(scenario1Act, &QAction::triggered, this, &MainWindow::scenario1);

    scenario2Act = new QAction(tr("&Scenariusz 2"), this);
    connect(scenario2Act, &QAction::triggered, this, &MainWindow::scenario2);

    exitAct = new QAction(tr("&Koniec"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    exitAct->setStatusTip(tr("Zamknij aplikacjê"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addStreetAct = new QAction(tr("&Ulica"), this);
    addStreetAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    addStreetAct->setStatusTip(tr("Dodaj ulicê"));
    connect(addStreetAct, &QAction::triggered, this, &MainWindow::addStreet);

    addParkingAct = new QAction(tr("&Parking"), this);
    addParkingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    addParkingAct->setStatusTip(tr("Dodaj parking"));
    connect(addParkingAct, &QAction::triggered, this, &MainWindow::addParking);

    addCameraAct = new QAction(tr("&Kamera"), this);
    addCameraAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    addCameraAct->setStatusTip(tr("Dodaj kamerê"));
    connect(addCameraAct, &QAction::triggered, this, &MainWindow::addCamera);

    addBuildingAct = new QAction(tr("&Budynek"), this);
    addBuildingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    addBuildingAct->setStatusTip(tr("Dodaj budynek"));
    connect(addBuildingAct, &QAction::triggered, this, &MainWindow::addBuilding);

    addCarAct = new QAction(tr("&Samochód"), this);
    addCarAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_C));
    addCarAct->setStatusTip(tr("Dodaj samochód"));
    connect(addCarAct, &QAction::triggered, this, &MainWindow::addCar);

    addTruckAct = new QAction(tr("&Ciê¿arówka"), this);
    addTruckAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_T));
    addTruckAct->setStatusTip(tr("Dodaj ciê¿arówkê"));
    connect(addTruckAct, &QAction::triggered, this, &MainWindow::addTruck);

    aboutAct = new QAction(tr("&O Autorach"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Plik"));
    fileMenu->addAction(scenario1Act);
    fileMenu->addAction(scenario2Act);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    objectsMenu = menuBar()->addMenu(tr("&Obiekty"));
    objectsMenu->addAction(addStreetAct);
    objectsMenu->addAction(addParkingAct);
    objectsMenu->addAction(addCameraAct);
    objectsMenu->addAction(addBuildingAct);
    objectsMenu->addSeparator();

    vehiclesMenu = menuBar()->addMenu(tr("&Pojazdy"));
    vehiclesMenu->addAction(addCarAct);
    vehiclesMenu->addAction(addTruckAct);
    vehiclesMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&O Autorach"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.exec(event->globalPos());
}

void MainWindow::scenario1() {

}
void MainWindow::scenario2() {

}
void MainWindow::addStreet() {

}
void MainWindow::addParking() {

}
void MainWindow::addCamera() {

}
void MainWindow::addBuilding() {

}
void MainWindow::addCar() {

}
void MainWindow::addTruck() {

}
void MainWindow::about() {
    QMessageBox::about(this, tr("About Menu"),
        tr("The <b>Menu</b> example shows how to create "
            "menu-bar menus and context menus."));
}