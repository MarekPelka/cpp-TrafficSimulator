/**
* \class CameraPopup
* \brief popup for camera construction
* \details simple gui popup with lineedits for user input to 
* construct camera object with specified properties
* \author Michal Krzeminski
*/

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
    ///destructor
    ~CameraPopup();
    /// constructor with given position
    void CameraPopupShow(Position position);
    ///set pointer to main application window
    void setMainWindow(std::shared_ptr<MainWindow> mw);
    ///singleton getInstance
    static CameraPopup* getInstance();

    public slots:
    ///slot for popup hide
    void CameraPopupHide();
private:
    ///pointer to main application window
    std::shared_ptr<MainWindow> mainwindow;
    ///singleton instance pointer
    static CameraPopup* instance;
    ///private default constructor
    CameraPopup();

    ///position of popup
    Position position;
    ///QT lineedit for direction user input
    QLineEdit *directionLineEdit;
    ///QT lineedit for angle user input
    QLineEdit *angleLineEdit;
    ///QT button accept
    QPushButton *buttonOk;
};
#endif