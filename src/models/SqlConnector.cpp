#include "SqlConnector.h"

SqlConnector* SqlConnector::instance = nullptr;

SqlConnector* SqlConnector::getInstance() {
    if (!instance) {
        instance = new SqlConnector;
    }
    return instance;
}

SqlConnector::SqlConnector() {}

bool SqlConnector::connect() {
    if(!QFile::exists("cam_observations.db")){
        return false;
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cam_observations.db");
    bool ok = db.open();
    return ok;
}

void SqlConnector::insert(int cam_id, std::string time, int x, int y) {
    QSqlQuery query;
    query.prepare("INSERT INTO 'history' ('camera_id', 'timestamp', 'x', 'y') "
        "VALUES (?, ?, ?, ?)");
    query.addBindValue(cam_id);
    query.addBindValue(time.c_str());
    query.addBindValue(x);
    query.addBindValue(y);
    query.exec();
}

void SqlConnector::disconnect() {
    db.close();
}