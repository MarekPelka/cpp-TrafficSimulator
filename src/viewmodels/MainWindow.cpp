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

    //dropdown menu
    createActions();
    createMenus();

    CameraPopup *popup = CameraPopup::getInstance();
    popup->setMainWindow(std::shared_ptr<MainWindow>(this));
    popup->setWindowFlags(Qt::Popup);
    popup->setParent(this);
    popup->move(0,300);
    popup->hide();

    setWindowTitle(QStringLiteral("Symulator ruchu miejskiego"));

    //initialize controllers
    //VehicleController::getInstance()->setMainWindow(std::shared_ptr<MainWindow>(this));

    //Painting streets
    //TODO: There is some weird auto-scaling/positioning -> understend and fix
    scene = new QGraphicsScene(ui->graphicsView);
    scene->setBackgroundBrush(Qt::darkGreen);
    ui->graphicsView->setScene(scene);

    streetGroup = new QGraphicsItemGroup();
    parkingGroup = new QGraphicsItemGroup();
    nodeGroup = new QGraphicsItemGroup();
    vehicleGroup = new QGraphicsItemGroup();
    pedestrianGroup = new QGraphicsItemGroup();
    parkingGroup->setZValue(100);
    //Order is important
    scene->addItem(streetGroup);
    scene->addItem(nodeGroup);
    scene->addItem(vehicleGroup);
    scene->addItem(pedestrianGroup);
    scene->addItem(parkingGroup);

    //label with info about current state of insert
    infoLabel = new QLabel(ui->graphicsView);
    infoLabel->setAlignment(Qt::AlignBottom);
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setStyleSheet("QLabel { color : white; }");
    infoLabel->setGeometry(QRect(20, 20, 80, LABEL_HEIGHT));
    //scene->addWidget(infoLabel);

    infoLabel->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow() {
    killTimer(timerId);
    CameraPopup::getInstance()->setParent(nullptr);
    delete ui;
}

void MainWindow::updateVehiclesViews() {

    VehicleController *vehC = VehicleController::getInstance();
    std::list<QGraphicsRectItem*> vehicleGraphics = GraphicFab::getVehiclesGraphics(vehC);
    scene->removeItem(vehicleGroup);
    delete vehicleGroup;
    vehicleGroup = new QGraphicsItemGroup();
    for (Vehicle veh : vehC->getVehicles()) {
        if (veh.color.size() != 0) {
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
            vehicleGroup->addToGroup(vehicleGraphics.front());
            vehicleGraphics.pop_front();
        }
    }
    scene->addItem(vehicleGroup);
    //scene->addItem(parkingGroup);
}

void MainWindow::updatePedestriansViews() {

    VehicleController *vehC = VehicleController::getInstance();
    std::list<QGraphicsEllipseItem*> pedestrianGraphics = GraphicFab::getPedestriansGraphics(vehC);
    scene->removeItem(pedestrianGroup);
    delete pedestrianGroup;
    pedestrianGroup = new QGraphicsItemGroup();
    for (auto p : vehC->getPedestrians()) {
        pedestrianGroup->addToGroup(pedestrianGraphics.front());
        pedestrianGraphics.pop_front();
    }
    scene->addItem(pedestrianGroup);
}

void MainWindow::paintStreets() {
    CityController *cityC = CityController::getInstance();
    for (QGraphicsItem* g : GraphicFab::getStreetsGraphics(cityC)) {
        streetGroup->addToGroup(g);
    }
}

void MainWindow::paintParkings() {
    CityController *cityC = CityController::getInstance();
    for (QGraphicsItem* g : GraphicFab::getParkingGraphics(cityC)) {
        parkingGroup->addToGroup(g);
    }
}

void MainWindow::paintIntersections() {
    CityController *cityC = CityController::getInstance();
    for (QGraphicsItem* g : GraphicFab::getIntersectionsGraphics(cityC)) {
        nodeGroup->addToGroup(g);
    }
}

std::list<PNode> MainWindow::nodesPath(Position start, Position end) {
    std::list<PNode> nodes = {};
    CityController *cityC = CityController::getInstance();
    std::list<PNode> allNodes = cityC->getNodes();
    PNode s = NULL;
    PNode e = NULL;
    //finding start node
    for (PNode node : allNodes) {
        if (checkClosest(*node, start)) {
            s = node;
        }
    }
    //finding end node
    for (PNode node : allNodes) {
        if (checkClosest(*node, end)) {
            e = node;
        }
    }
    if (s == NULL || e == NULL)
        return nodes;
    for (std::list<PNode> w : cityC->getWay(s)) {
        if (w.back() == e)
            nodes = w;
    }
    return nodes;
}

bool MainWindow::checkClosest(Node node, Position position) {
    if (position.x < node.getPosition().x + CLOSEST_NODE
        && position.x > node.getPosition().x - CLOSEST_NODE
        && position.y < node.getPosition().y + CLOSEST_NODE
        && position.y > node.getPosition().y - CLOSEST_NODE) {
        return true;
    }
    else {
        return false;
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    VehicleController *vehC = VehicleController::getInstance();
    vehC->updatePositions(int(1000 / FPS));
    this->updateVehiclesViews();
    this->updatePedestriansViews();

    CameraController *camC = CameraController::getInstance();
    camC->updateObservations();
    camC->writeToFile("CameraObservations.txt");

    if (randomMovement) {
        ParkingController::getInstance()->randomSpawnVehicle(FPS);
        ParkingController::getInstance()->randomSpawnPedestrian(FPS);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QString status = infoLabel->text();
    VehicleController *vehC = VehicleController::getInstance();
    CityController *cityC = CityController::getInstance();
    std::list<PNode> nodes;
    if (status.size() != 0) {
        QPointF point = ui->graphicsView->mapToScene(event->pos());
        Position position(point.x(), point.y() - LABEL_HEIGHT);

        if (status == "Ulica" && click == false) {
            PNode first = nullptr;
            for (PNode node : cityC->getNodes()) {
                if (checkClosest(*node, position)) {
                    first = node;
                    break;
                }
            }
            if (first) {
                click = true;
                startPos = first->getPosition();
            }
        }
        else if (status == "Ulica" && click == true) {
            endPos = position;
            if (atan2(startPos.y - endPos.y, startPos.x - endPos.x) * 180 / M_PI > 45) {
                endPos = Position(startPos.x, endPos.y);
            }
            else {
                endPos = Position(endPos.x, startPos.y);
            }
            cityC->addStreet(startPos, endPos);
            //TO CONSIDER add diffrently paint
            paintIntersections();
            paintStreets();
            click = false;
        }
        else if (status == "Budynek") {
            if (!checkIfIntersectStreet(position)) {
                Building building(position);
                CameraController::getInstance()->addBuilding(building);
                QRect buildingRect(position.x, position.y, BUILDING_SIZE, BUILDING_SIZE);
                //RGB grey color
                QBrush brush = QBrush(QColor(152, 152, 152));
                //black border solid
                QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
                scene->addRect(buildingRect, pen, brush);
            }
        }
        else if (status == "Parking") {
            PNode toUpgrade = nullptr;
            for (PNode node : cityC->getNodes()) {
                if (checkClosest(*node, position)) {
                    toUpgrade = node;
                    break;
                }
            }
            if (toUpgrade) {
                cityC->upgradeToParking(toUpgrade);
            }
            //TO CONSIDER add diffrently paint
            paintParkings();
        }
        else if (status == "Kamera") {
            CameraPopup::getInstance()->CameraPopupShow(position);
        }
        else if (status == QStringLiteral("Samochód") && click == false) {
            click = true;
            startPos = position;
        }
        else if (status == QStringLiteral("Samochód") && click == true) {
            endPos = position;
            nodes = nodesPath(startPos, endPos);
            if (!nodes.empty()) {
                Vehicle car(CAR, nodes);
                vehC->addVehicle(car);
            }
            click = false;
        }
        else if (status == QStringLiteral("Ciê¿arówka") && click == false) {
            click = true;
            startPos = position;
        }
        else if (status == QStringLiteral("Ciê¿arówka") && click == true) {
            endPos = position;
            nodes = nodesPath(startPos, endPos);
            if (!nodes.empty()) {
                Vehicle truck(TRUCK, nodes);
                vehC->addVehicle(truck);
            }
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

	randomMovmentAct = new QAction(tr("&Ruch losowy"), this);
	connect(randomMovmentAct, &QAction::triggered, this, &MainWindow::randomMovment);

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
	fileMenu->addAction(randomMovmentAct);
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

    paintStreets();
    paintIntersections();
    paintParkings();
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

	std::list<PNode> nodes = nodesPath(p4, p1);
	if (!nodes.empty()) {
		for (int i = 0; i < 20; i++) {
			Vehicle car(CAR, nodes);
			VehicleController::getInstance()->addVehicle(car);
		}
	}
	paintStreets();
	paintIntersections();
	paintParkings();
}
void MainWindow::randomMovment()
{
	randomMovement = !randomMovement;
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

void MainWindow::cameraPopupHide(Position pos, int angle, QString di) {
  char direction = di.toLatin1().data()[0];
    Direction dir=NONE;
    if (direction == 'N') {
        dir = N;
    }
    else if (direction == 'S') {
        dir = S;
    }
    else if (direction == 'E') {
        dir = E;
    }
    else if (direction == 'W') {
        dir = W;
    }
    Camera camera(pos, angle, dir);
    CameraController::getInstance()->addCamera(camera);
    QRect cam(pos.x, pos.y, CAMERA_SIZE, CAMERA_SIZE);
    //RGB red color
    QBrush brush = QBrush(QColor(255, 0, 0));
    //black border solid
    QPen pen = QPen(QColor(0, 0, 0), 1, Qt::SolidLine);
    scene->addEllipse(cam, pen, brush);
}

bool MainWindow::checkIfIntersectStreet(Position position)
{
    for (auto street : CityController::getInstance()->getStreets()) {
        //TODO if street twoway check two edges of street (main line +- STREET_WIDTH)
        //TODO if street not twoway check correct edge and main line
        int offset = STREET_WIDTH;
        if (street->hasSidewalk()) {
            offset += SIDEWALK_WIDTH;
        }

        //check middle line
        Position p1 = street->getStartEndPositions().first;
        Position p2 = street->getStartEndPositions().second;
        if (CameraController::getInstance()->LineIntersectsLine(p1, p2, position, Position(position.x + BUILDING_SIZE, position.y)) ||
            CameraController::getInstance()->LineIntersectsLine(p1, p2, position, Position(position.x, position.y + BUILDING_SIZE)) ||
            CameraController::getInstance()->LineIntersectsLine(p1, p2, Position(position.x + BUILDING_SIZE, position.y + BUILDING_SIZE), Position(position.x + BUILDING_SIZE, position.y)) ||
            CameraController::getInstance()->LineIntersectsLine(p1, p2, Position(position.x + BUILDING_SIZE, position.y + BUILDING_SIZE), Position(position.x, position.y + BUILDING_SIZE))) {
            return true;
        }

        //check outer edge
        Position q1;
        Position q2;
        switch (street->getDirection()) {
        case N: {
            q1 = Position(p1.x + offset, p1.y);
            q2 = Position(p2.x + offset, p2.y);
            break;
        }
        case S: {
            q1 = Position(p1.x - offset, p1.y);
            q2 = Position(p2.x - offset, p2.y);
            break;
        }
        case E: {
            q1 = Position(p1.x, p1.y + offset);
            q2 = Position(p2.x, p2.y + offset);
            break;
        }
        case W: {
            q1 = Position(p1.x, p1.y - offset);
            q2 = Position(p2.x, p2.y - offset);
            break;
        }
        default: {
            q1 = Position(0, 0);
            q2 = Position(0, 0);
        }
        }
        if (CameraController::getInstance()->LineIntersectsLine(q1, q2, position, Position(position.x + BUILDING_SIZE, position.y)) ||
            CameraController::getInstance()->LineIntersectsLine(q1, q2, position, Position(position.x, position.y + BUILDING_SIZE)) ||
            CameraController::getInstance()->LineIntersectsLine(q1, q2, Position(position.x + BUILDING_SIZE, position.y + BUILDING_SIZE), Position(position.x + BUILDING_SIZE, position.y)) ||
            CameraController::getInstance()->LineIntersectsLine(q1, q2, Position(position.x + BUILDING_SIZE, position.y + BUILDING_SIZE), Position(position.x, position.y + BUILDING_SIZE))) {
            return true;
        }
    }
    return false;
}