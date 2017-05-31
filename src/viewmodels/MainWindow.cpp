#include "MainWindow.h"
#include "../../GeneratedFiles/ui_mainwindow.h"
#include "../models/Building.h"
#include "../models/Camera.h"
#include "../views/CameraPopup.h"
#include "../Enums.h"
#include "CameraController.h"
#include "CityController.h"
#include "ParkingController.h"
#include "GraphicFab.h"
#include <QGraphicsItem>
#include <QString>
#include <QtWidgets>

typedef std::shared_ptr<Node> PNode;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	createActions();
	createMenus();

	setWindowTitle(QStringLiteral("Symulator ruchu miejskiego"));
	setWindowIcon(QIcon("images/Traffic-50.png"));
	scene = new CityScene(this);
	setCentralWidget(scene);

	infoLabel = new QLabel("Status label!");
	infoLabel->setAlignment(Qt::AlignBottom);
	infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	infoLabel->setStyleSheet("QLabel { color : white; }");
	infoLabel->setGeometry(QRect(20, 20, 80, LABEL_HEIGHT));
}

MainWindow::~MainWindow() {
	killTimer(timerId);
	CameraPopup::getInstance()->setParent(nullptr);
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
	connect(exitAct, &QAction::triggered, this, &QWidget::close);

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
	//timer for vehicle movement
	//timerId = startTimer(1000 / FPS);
	timerPosition = new QTimer(this);
	connect(timerPosition, SIGNAL(timeout()), this, SLOT(timerEventPos()));
	timerPosition->start(1000 / FPS);
	timerDatabase = new QTimer(this);
	connect(timerDatabase, SIGNAL(timeout()), this, SLOT(timerEventDatabase()));
	timerDatabase->start(1000);
}

void MainWindow::timerEventPos() {
	MovementController *moveC = MovementController::getInstance();
	moveC->updatePositions(int(1000 / FPS), careForOthers);
	//this->updateVehiclesViews();
	//this->updatePedestriansViews();

	if (randomMovement) {
		ParkingController::getInstance()->randomSpawnVehicle(FPS);
		ParkingController::getInstance()->randomSpawnPedestrian(FPS);
	}

	scene->refresh();
}

void MainWindow::randomMovment() {
	randomMovement = !randomMovement;
}

void MainWindow::care() {
	careForOthers = !careForOthers;
}

void MainWindow::scenario1() {
	CityController *cityC = CityController::getInstance();
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
	Position pc3(300, 0);
	Position pc4(300, 600);
	cityC->addStreet(pc3, pc4);
	Position pc1(0, 300);
	Position pc2(600, 300);
	cityC->addStreet(pc1, pc2);

	cityC->upgradeToParking(cityC->findNode(Position(100, 100)));
	cityC->upgradeToParking(cityC->findNode(Position(500, 500)));
	cityC->upgradeToParking(cityC->findNode(Position(300, 300)));

	Position p11(50, 50);
	Position p12(50, 550);
	Position p13(550, 550);
	Position p14(550, 50);

	cityC->addStreet(p11, p12, true);
	cityC->addStreet(p12, p13, true);
	cityC->addStreet(p13, p14, true);
	cityC->addStreet(p14, p11, true);

	cityC->upgradeToParking(cityC->findNode(Position(50, 550)));
	cityC->upgradeToParking(cityC->findNode(Position(550, 50)));
	scene->refresh();
}
void MainWindow::scenario2() {
	CityController *cityC = CityController::getInstance();
	Position p1(100, 100);
	Position p2(500, 100);
	Position p3(500, 500);
	Position p4(100, 500);

	cityC->addStreet(p1, p2);
	cityC->addStreet(p2, p3);
	cityC->addStreet(p3, p4);

	cityC->addStreet(p2, p1);
	cityC->addStreet(p3, p2);
	cityC->addStreet(p4, p3);
}

void MainWindow::about() {
	QMessageBox::about(this, tr("O Autorach"),
		QStringLiteral("<b>Autorzy:</b> Micha³ Krzemiñski i Marek Pelka"));
}