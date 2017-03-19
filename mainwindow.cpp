#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CitiController.h"
#include "Position.h"
#include "Street.h"
#include "Node.h"
#include <QGraphicsLineItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CitiController *citiC = new CitiController(this);

	//TESTING FOR CITI TOPOLOGY
	Position *p1 = new Position(10, 10);
	Position *p2 = new Position(50, 50);
	Position *p3 = new Position(10, 500);
	citiC->addStreet(p1, p2);
	citiC->addStreet(p2, p3);
	citiC->addStreet(p3, p1);
	
	//Painting streets
	//TO DO: There is some weird auto-scaling/positioning -> understend and fix
	QGraphicsScene* scene = new QGraphicsScene(ui->graphicsView);
	scene->setBackgroundBrush(Qt::green);
	ui->graphicsView->setScene(scene);
	for (QGraphicsItem* g : citiC->getStreetsGraphics())
	{
		scene->addItem(g);
	}
	
}

MainWindow::~MainWindow()
{
    delete ui;
}
