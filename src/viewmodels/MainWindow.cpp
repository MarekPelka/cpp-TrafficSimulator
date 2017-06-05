#include "MainWindow.h"
#include "../../GeneratedFiles/ui_mainwindow.h"
#include "../models/Building.h"
#include "../models/Camera.h"
#include "../Enums.h"
#include "CameraController.h"
#include "CityController.h"
#include "ParkingController.h"
#include "GraphicFab.h"
#include <QGraphicsItem>
#include <QString>
#include <QtWidgets>
#include <thread>

typedef std::shared_ptr<Node> PNode;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	createActions();
	createMenus();

	setWindowTitle(QStringLiteral("Symulator ruchu miejskiego"));
	//setWindowIcon(QIcon("images/Traffic-50.png"));
	scene = new CityScene(this);
	setCentralWidget(scene);
}

MainWindow::~MainWindow() {
	//CameraPopup::getInstance()->setParent(nullptr);
	delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
	QMenu menu(this);
	menu.exec(event->globalPos());
}

void MainWindow::createActions() {
	startAct = new QAction(tr("&Start"), this);
	connect(startAct, &QAction::triggered, this, &MainWindow::start);

	scenario1Act = new QAction(tr("&Scenariusz 1"), this);
	connect(scenario1Act, &QAction::triggered, this, &MainWindow::scenario1);

	scenario2Act = new QAction(tr("&Scenariusz 2"), this);
	connect(scenario2Act, &QAction::triggered, this, &MainWindow::scenario2);

	randomMovmentAct = new QAction(tr("&Ruch losowy"), this);
	connect(randomMovmentAct, &QAction::triggered, this, &MainWindow::randomMovment);

	careForOthersAct = new QAction(tr("&Ruch bezkolizyjny"), this);
	connect(careForOthersAct, &QAction::triggered, this, &MainWindow::care);

	exitAct = new QAction(tr("&Koniec"), this);
	exitAct->setShortcuts(QKeySequence::Close);
	connect(exitAct, &QAction::triggered, this, &MainWindow::close);

	addStreetAct = new QAction(tr("&Ulica"), this);
	addStreetAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	addStreetAct->setIconVisibleInMenu(true);
	connect(addStreetAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::addStreet); });

	addParkingAct = new QAction(tr("&Parking"), this);
	addParkingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	connect(addParkingAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::toggleParking); });

	addCameraAct = new QAction(tr("&Kamera"), this);
	addCameraAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
	connect(addCameraAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::addCamera); });

	addBuildingAct = new QAction(tr("&Budynek"), this);
	addBuildingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
	connect(addBuildingAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::addBuilding); });

	deletingAct = new QAction(tr("&Usuwanie"), this);
	deletingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
	connect(deletingAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::remove); });

	addCarAct = new QAction(QStringLiteral("&Samochód"), this);
	addCarAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_C));
	connect(addCarAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::addCar); });

	addTruckAct = new QAction(QStringLiteral("&Ciê¿arówka"), this);
	addTruckAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_T));
	connect(addTruckAct, &QAction::triggered, this, [=] () {scene->setOperation(CityScene::Operation::addTruck); });

	aboutAct = new QAction(tr("&O Autorach"), this);
	connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
	fileMenu = menuBar()->addMenu(tr("&Plik"));
	fileMenu->addAction(startAct);
	fileMenu->addAction(scenario1Act);
	fileMenu->addAction(scenario2Act);
	fileMenu->addAction(randomMovmentAct);
	fileMenu->addAction(careForOthersAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	objectsMenu = menuBar()->addMenu(tr("&Obiekty"));
	objectsMenu->addAction(addStreetAct);
	objectsMenu->addAction(addParkingAct);
	objectsMenu->addAction(addCameraAct);
	objectsMenu->addAction(addBuildingAct);
	objectsMenu->addAction(deletingAct);
	objectsMenu->addSeparator();

	vehiclesMenu = menuBar()->addMenu(tr("&Pojazdy"));
	vehiclesMenu->addAction(addCarAct);
	vehiclesMenu->addAction(addTruckAct);
	vehiclesMenu->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&O Autorach"));
	helpMenu->addAction(aboutAct);
	helpMenu->addSeparator();

	//to show menu on linux
	menuBar()->setNativeMenuBar(false);
}

void MainWindow::start() {
	timerPosition = new QTimer(this);
	connect(timerPosition, SIGNAL(timeout()), this, SLOT(timerEventPos()));
	timerPosition->start(1000 / FPS);
	timerDatabase = new QTimer(this);
	connect(timerDatabase, SIGNAL(timeout()), this, SLOT(timerEventDatabase()));
	timerDatabase->start(1000);
}

void MainWindow::timerEventPos() {
    if (end_flag)
        return;
	MovementController *moveC = MovementController::getInstance();
	moveC->updatePositions(int(1000 / FPS), careForOthers);

	if (randomMovement) {
		ParkingController::getInstance()->randomSpawnVehicle(FPS);
		ParkingController::getInstance()->randomSpawnPedestrian(FPS);
	}

	scene->refresh();
}

void MainWindow::timerEventDatabase() {
	std::thread(&MainWindow::saveToDatabaseCallback, this).detach();
}

void MainWindow::saveToDatabaseCallback() {
    if (end_flag)
        return;
	CameraController *camC = CameraController::getInstance();
	camC->updateObservations();
	if (camC->insertType) {
		camC->writeToDatabase();
	} else {
		camC->writeToFile("CameraObservations.txt");
	}
}

void MainWindow::randomMovment() {
	randomMovement = !randomMovement;
}

void MainWindow::care() {
	careForOthers = !careForOthers;
}

void MainWindow::close() {
    end_flag = true;
    if(timerPosition)
        if(timerPosition->isActive())
            timerPosition->stop();
    if (timerDatabase)
        if (timerDatabase->isActive())
            timerDatabase->stop();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    CameraController::getInstance()->DescCameraController();
    SqlConnector::getInstance()->DescSqlConnector();
    ParkingController::getInstance()->DescParkingController();

    CityController::getInstance()->DescCityController();
    MovementController::getInstance()->DescMovementController();
    QWidget::close();
}

void MainWindow::scenario1() {
	CityController *cityC = CityController::getInstance();
	double GAP = FULL_STREET_WIDTH * 2;
	Position p1(GAP * 4, GAP * 4);
	Position p2(GAP * 15, GAP * 4);
	Position p3(GAP * 15, GAP * 15);
	Position p4(GAP * 4, GAP * 15);

	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);
	cityC->addStreet(p4, p1);

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
	cityC->addStreet(p1, p4);
	//Crossing
	Position pc3(GAP * 10, GAP * 2);
	Position pc4(GAP * 10, GAP * 17);
	cityC->addStreet(pc3, pc4);
	Position pc1(GAP * 2, GAP * 10);
	Position pc2(GAP * 17, GAP * 10);
	cityC->addStreet(pc1, pc2);

	cityC->upgradeToParking(cityC->findNode(Position(GAP * 4, GAP * 4)));
	cityC->upgradeToParking(cityC->findNode(Position(GAP * 15, GAP * 15)));
	cityC->upgradeToParking(cityC->findNode(Position(GAP * 10, GAP * 10)));

	scene->refresh();
}
void MainWindow::scenario2() {
	CityController *cityC = CityController::getInstance();
	double GAP = FULL_STREET_WIDTH * 2;
	Position p1(GAP * 1, GAP * 1);
	Position p2(GAP * 12, GAP * 1);
	Position p3(GAP * 12, GAP * 12);
	Position p4(GAP * 1, GAP * 12);

	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
	std::list<PNode> nodes = CityController::getInstance()->nodesPath(p4, p1);
	if (!nodes.empty()) {
		for (int i = 0; i < 20; i++) {
			Vehicle car(CAR, nodes);
			MovementController::getInstance()->addVehicle(car);
		}
	}
	scene->refresh();
}

void MainWindow::about() {
	QMessageBox::about(this, tr("O Autorach"),
		QStringLiteral("<b>Autorzy:</b> Micha³ Krzemiñski i Marek Pelka"));
}