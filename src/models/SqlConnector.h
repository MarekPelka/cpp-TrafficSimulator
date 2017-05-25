#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QtSql>
#include <QString>

class SqlConnector {
public:
    static SqlConnector* getInstance();
    bool connect();
    void insert(int cam_id, std::string time, int x, int y);
    void disconnect();

private:
    SqlConnector();
    static SqlConnector* instance;

    QSqlDatabase db;

    QString host = "127.0.0.1";
    QString user = "root";
    QString pass = "";
};
#endif