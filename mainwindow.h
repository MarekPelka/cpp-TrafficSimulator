#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	boost::signals2::signal<void(int)> sigUpdatePositions;
	void updateVehiclesViews();
	void paintVehicles(std::list<QRect*> vehicleGraphics);
private:
    Ui::MainWindow *ui;
	int timerId;
	QGraphicsScene *scene;
protected:
	void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
