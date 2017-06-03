#include "CameraPopup.h"

CameraPopup* CameraPopup::instance = nullptr;

CameraPopup* CameraPopup::getInstance() {
    if (!instance)
        instance = new CameraPopup;
    return instance;
}

void CameraPopup::setMainWindow(std::shared_ptr<MainWindow> mw) {
    mainwindow = mw;
}

CameraPopup::CameraPopup()
{
    directionLineEdit = new QLineEdit(this);
    directionLineEdit->setPlaceholderText("Kierunek");
    angleLineEdit = new QLineEdit(this);
    angleLineEdit->setPlaceholderText(QStringLiteral("K¹t"));
    buttonOk = new QPushButton("Ok", this);
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(CameraPopupHide()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(directionLineEdit);
    layout->addWidget(angleLineEdit);
    layout->addWidget(buttonOk);
    setLayout(layout);

    setWindowTitle("Parametry kamery");
    setFixedSize(100,100);
    setStyleSheet("background-color: white");
}

CameraPopup::~CameraPopup() {
    if (instance) {
        delete directionLineEdit;
        delete angleLineEdit;
        delete buttonOk;
        delete instance;
    }
}

void CameraPopup::CameraPopupShow(Position pos) {
    position = pos;
    this->show();
}

void CameraPopup::CameraPopupHide()
{
    this->hide();
    QString direction = directionLineEdit->text();
    QString angle = angleLineEdit->text();
    //mainwindow->cameraPopupHide(position, angle.toInt(), direction);
}