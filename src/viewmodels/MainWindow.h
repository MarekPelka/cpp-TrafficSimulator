/**
* \class MainWindow
* \ingroup viewmodels
* \details class controlling main window, actions, menu and gui
* \author Micha³ Krzemiñski
* \author Marek Pelka
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <list>
#include <memory>
#include "../models/Position.h"
#include "../models/Vehicle.h"

namespace Ui {
    class MainWindow;
}

class QAction;
class QMenu;
class QLabel;

typedef std::shared_ptr<Node> PNode;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateVehiclesViews();
    void updatePedestriansViews();
    void paintStreets();
    void paintParkings();
    void paintIntersections();
    void cameraPopupHide(Position pos, int angle, QString direction);
    std::list<PNode> nodesPath(Position start, Position end);

private:
    Ui::MainWindow *ui;
    int timerId;
    QGraphicsScene *scene;
    QGraphicsItemGroup * streetGroup;
    QGraphicsItemGroup * parkingGroup;
    QGraphicsItemGroup * nodeGroup;
    QGraphicsItemGroup * vehicleGroup;
    QGraphicsItemGroup * pedestrianGroup;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    QTimer * timerPosition;
    QTimer * timerDatabase;
    //dropdown menu
    void contextMenuEvent(QContextMenuEvent *event) override;

    private slots:
    void start();
    void scenario1();
    void scenario2();
	void randomMovment();
    void addStreet();
    void addParking();
    void addCamera();
    void addBuilding();
    void addCar();
    void addTruck();
    void about();
    void timerEventDatabase();
    void timerEventPos();

private:
    void createActions();
    void createMenus();
    QMenu *fileMenu;
    QMenu *objectsMenu;
    QMenu *vehiclesMenu;
    QMenu *helpMenu;
    QAction *startAct;
    QAction *scenario1Act;
    QAction *scenario2Act;
	QAction *randomMovmentAct;
    QAction *exitAct;
    QAction *addStreetAct;
    QAction *addParkingAct;
    QAction *addCameraAct;
    QAction *addBuildingAct;
    QAction *addCarAct;
    QAction *addTruckAct;
    QAction *aboutAct;
    //label with info about current state of insert
    QLabel *infoLabel;

    //start and end positions for vehicle adding and flag
    Position startPos;
    Position endPos;
    bool click = false;
    bool randomMovement = false;
    bool checkClosest(Node node, Position position);
    bool checkIfIntersectStreet(Position position);
};

#endif // MAINWINDOW_H
