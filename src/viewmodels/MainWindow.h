#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <list>
#include "../models/Position.h"
#include "../models/Vehicle.h"

namespace Ui {
	class MainWindow;
}

class QAction;
class QMenu;
class QLabel;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void updateVehiclesViews();
	void paintStreets();
	void paintIntersections();
    std::list<Node*> nodesPath(Position start, Position end);
private:
	Ui::MainWindow *ui;
	int timerId;
	QGraphicsScene *scene;
	QGraphicsItemGroup * streetGroup;
	QGraphicsItemGroup * nodeGroup;
	QGraphicsItemGroup * vechicleGroup;
protected:
    void timerEvent(QTimerEvent *event);
    void mousePressEvent(QMouseEvent *event) override;

    //dropdown menu
    void contextMenuEvent(QContextMenuEvent *event) override;

    private slots:
        void start();
        void scenario1();
        void scenario2();
        void addStreet();
        void addParking();
        void addCamera();
        void addBuilding();
        void addCar();
        void addTruck();
        void about();
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
    bool click = false;
    Position startPos;
    Position endPos;
    QImage image;
    bool checkClosest(Node node, Position position);
    bool checkIfIntersectStreet(Position position, int radius);
};

#endif // MAINWINDOW_H
