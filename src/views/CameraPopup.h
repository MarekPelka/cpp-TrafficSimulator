#ifndef CAMERAPOPUP_H
#define CAMERAPOPUP_H

#include "../viewmodels/MainWindow.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QStyle>

class CameraPopup : public QWidget
{
    Q_OBJECT

public:
    void CameraPopupShow(Position position);
    void setMainWindow(std::shared_ptr<MainWindow> mw);
    static CameraPopup* getInstance();

    public slots:
    void CameraPopupHide();
private:
    std::shared_ptr<MainWindow> mainwindow;
    static CameraPopup* instance;
    CameraPopup();

    Position position;
    QLineEdit *directionLineEdit;
    QLineEdit *angleLineEdit;
    QPushButton *buttonOk;
};
#endif