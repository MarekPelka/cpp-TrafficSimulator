#include "MainWindow.h"
#include "../../GeneratedFiles/ui_mainwindow.h"
#include "../models/Building.h"
#include "../models/Camera.h"
#include "../Enums.h"
#include "CityController.h"
#include "GraphicFab.h"
#include <QGraphicsItem>
#include <QString>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

    //dropdown menu
    createActions();
    createMenus();

    setWindowTitle(QStringLiteral("Symulator ruchu miejskiego"));

    //initialize controllers
	VehicleController *vehC = VehicleController::getInstance();
	vehC->setMainWindow(this);

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

    //label with info about current state of insert
    infoLabel = new QLabel(ui->graphicsView);
    infoLabel->setAlignment(Qt::AlignBottom);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setStyleSheet("QLabel { color : white; }");
    infoLabel->setGeometry(QRect(20, 20, 80, 20));
    //scene->addWidget(infoLabel);

    infoLabel->setFocusPolicy(Qt::NoFocus);
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

std::list<Node> MainWindow::nodesPath(Position start, Position end) {
    std::list<Node> nodes;
    CityController *cityC = CityController::getInstance();
    std::list<Node*> allNodes = cityC->getNodes();
    
    // finding start node
    for (Node* node : allNodes) {
        if (checkClosest(*node, start))
        {
            nodes.push_front(*node);
        }
    }
    //finding end node
    for (Node* node : allNodes) {
        if (checkClosest(*node, end))
        {
            nodes.push_back(*node);
        }
    }

    //TODO djikstra to return nodes that are between start and end
    return nodes;
}

bool MainWindow::checkClosest(Node node, Position position)
{
    if (position.x < node.getPosition().x + CLOSEST_NODE
        && position.x > node.getPosition().x - CLOSEST_NODE
        && position.y < node.getPosition().y + CLOSEST_NODE
        && position.y > node.getPosition().y - CLOSEST_NODE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    VehicleController *vehC = VehicleController::getInstance();
	vehC->updatePositions(int(1000 / FPS));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    bool stat = ui->graphicsView->hasFocus();
    bool stati = scene->hasFocus();
    QString status = infoLabel->text();
    VehicleController *vehC = VehicleController::getInstance();
    std::list<Node> nodes;
    if (status.size() != 0) {
        QPoint point(event->pos());
        //TODO X coordinate is shift about 50px, -50 to rescale
        Position position(point.x()-50, point.y());
        if(status == "Ulica") {

        }
        else if (status == "Budynek") {
            if (!checkIfIntersectStreet(position, BUILDING_SIZE)) {
                Building building(position);
                //TODO add to controller to store
                QRect buildingRect(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE);
                //RGB grey color
                QBrush brush = QBrush(QColor(152, 152, 152));
                //black border solid
                QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
                scene->addRect(buildingRect, pen, brush);
            }
        }
        else if (status == "Parking") {

        }
        else if (status == "Kamera") {
            if (checkIfIntersectStreet(position, CAMERA_SIZE)) {
                Camera camera(position);
                //TODO add camera to controller to store
                QRect cam(position.x, position.y, CAMERA_SIZE, CAMERA_SIZE);
                //RGB red color
                QBrush brush = QBrush(QColor(255, 0, 0));
                //black border solid
                QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
                scene->addEllipse(cam, pen, brush);
            }
        }
        else if (status == QStringLiteral("Samochód") && click == false) {
            click = true;
            startPos = position;
        }
        else if (status == QStringLiteral("Samochód") && click == true) {
            endPos = position;
            nodes = nodesPath(startPos, endPos);
            Vehicle car(CAR, nodes);
            vehC->addVehicle(car);
            click = false;
        }
        else if (status == QStringLiteral("Ciê¿arówka") && click == false) {
            click = true;
            startPos = position;
        }
        else if (status == QStringLiteral("Ciê¿arówka") && click == true) {
            endPos = position;
            nodes = nodesPath(startPos, endPos);
            Vehicle truck(TRUCK, nodes);
            vehC->addVehicle(truck);
            click = false;
        }
    }
}

void MainWindow::createActions() {
    startAct = new QAction(tr("&Start"), this);
    connect(startAct, &QAction::triggered, this, &MainWindow::start);

    scenario1Act = new QAction(tr("&Scenariusz 1"), this);
    connect(scenario1Act, &QAction::triggered, this, &MainWindow::scenario1);

    scenario2Act = new QAction(tr("&Scenariusz 2"), this);
    connect(scenario2Act, &QAction::triggered, this, &MainWindow::scenario2);

    exitAct = new QAction(tr("&Koniec"), this);
    exitAct->setShortcuts(QKeySequence::Close);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addStreetAct = new QAction(tr("&Ulica"), this);
    addStreetAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    addStreetAct->setIconVisibleInMenu(true);
    connect(addStreetAct, &QAction::triggered, this, &MainWindow::addStreet);

    addParkingAct = new QAction(tr("&Parking"), this);
    addParkingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    connect(addParkingAct, &QAction::triggered, this, &MainWindow::addParking);

    addCameraAct = new QAction(tr("&Kamera"), this);
    addCameraAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    connect(addCameraAct, &QAction::triggered, this, &MainWindow::addCamera);

    addBuildingAct = new QAction(tr("&Budynek"), this);
    addBuildingAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    connect(addBuildingAct, &QAction::triggered, this, &MainWindow::addBuilding);

    addCarAct = new QAction(QStringLiteral("&Samochód"), this);
    addCarAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_C));
    connect(addCarAct, &QAction::triggered, this, &MainWindow::addCar);

    addTruckAct = new QAction(QStringLiteral("&Ciê¿arówka"), this);
    addTruckAct->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_T));
    connect(addTruckAct, &QAction::triggered, this, &MainWindow::addTruck);

    aboutAct = new QAction(tr("&O Autorach"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&Plik"));
    fileMenu->addAction(startAct);
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

void MainWindow::start() {
    //timer for vehicle movement
    timerId = startTimer(1000 / FPS);
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
    Position pc3(300, 50);
    Position pc4(300, 550);
    cityC->addStreet(pc3, pc4);
    Position pc1(50, 300);
    Position pc2(550, 300);
    cityC->addStreet(pc1, pc2);

    paintStreets();
    paintIntersections();
}
void MainWindow::scenario2() {
	CityController *cityC = CityController::getInstance();
	VehicleController *vehC = VehicleController::getInstance();
	auto list = cityC->getWay(cityC->findNode(Position(100, 500)));
	list.pop_back();
	Vehicle car(CAR, list.back());
	vehC->addVehicle(car);
}
void MainWindow::addStreet() {
    infoLabel->setText(tr("Ulica"));
}
void MainWindow::addParking() {
    infoLabel->setText(tr("Parking"));
}
void MainWindow::addCamera() {
    infoLabel->setText(tr("Kamera"));
}
void MainWindow::addBuilding() {
    infoLabel->setText(tr("Budynek"));
}
void MainWindow::addCar() {
    infoLabel->setText(QStringLiteral("Samochód"));
}
void MainWindow::addTruck() {
    infoLabel->setText(QStringLiteral("Ciê¿arówka"));
}
void MainWindow::about() {
    QMessageBox::about(this, tr("O Autorach"),
        QStringLiteral("<b>Autorzy:</b> Micha³ Krzemiñski i Marek Pelka"));
}

bool MainWindow::checkIfIntersectStreet(Position position, int radius)
{
    //TODO get graph edges
    //for range all streets and check id building intersect
    return false;
}
