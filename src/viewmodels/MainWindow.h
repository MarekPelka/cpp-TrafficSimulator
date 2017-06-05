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
#include "../views/CityScene.h"

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
    ///constructor
    explicit MainWindow(QWidget *parent = 0);
    ///destructor for ui
    ~MainWindow();
private:
    ///qt gui main component
    Ui::MainWindow *ui;
    ///qt scene
	CityScene *scene;
protected:
    ///qt timer for updating moving object positions
    QTimer * timerPosition = nullptr;
    ///qt timer for inserting to database observations
    QTimer * timerDatabase = nullptr;
    ///qt dropdown menu event handler
    void contextMenuEvent(QContextMenuEvent *event) override;

    private slots:
    ///timers start
    void start();
    ///first scenario, simple city with few parkings and streets
    void scenario1();
    ///second scenario showing vehicle movement without collision
    void scenario2();
    ///toggle on/off random spawning moving objects
    void randomMovment();
    ///toggle movement with/without collisions
    void care();
    ///close application
    void close();
    ///open window with authors data
    void about();
    ///event firing on timerDatabase, iserting cameras observations to database/file
    void timerEventDatabase();
    ///callback for database insertion
	void saveToDatabaseCallback();
    ///event firing on timerPosition, updating objects positions and spawning new objects
    void timerEventPos();

private:
    ///creating actions for dropdown menus
    void createActions();
    ///creating dropdown menus
    void createMenus();
    QMenu *fileMenu;
    QMenu *objectsMenu;
    QMenu *vehiclesMenu;
    QMenu *helpMenu;
    QAction *startAct;
    QAction *scenario1Act;
    QAction *scenario2Act;
	QAction *randomMovmentAct;
	QAction *careForOthersAct;
    QAction *exitAct;
    QAction *addStreetAct;
    QAction *addParkingAct;
    QAction *addCameraAct;
    QAction *addBuildingAct;
	QAction *deletingAct;
    QAction *addCarAct;
    QAction *addTruckAct;
    QAction *aboutAct;

    ///flag for random spawning objects
    bool randomMovement = false;
    ///flag for collision free traffic
	bool careForOthers = true;
};

#endif // MAINWINDOW_H
