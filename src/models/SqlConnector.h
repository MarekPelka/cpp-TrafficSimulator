/**
 * \class SqlConnector
 * \ingroup models
 * \brief Sqlite database connection
 * \details Class dealing with connection/disconnection and insertion to sqlite database
 * \author Michal Krzeminski
*/

#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QtSql>
#include <QString>

class SqlConnector {
public:
    ///destructor
    void DescSqlConnector();
    ///singleton getInstance method
    static SqlConnector* getInstance();
    /** connect to sqlite database
    * \return bool connection status
    */
    bool connect();
    /**
    * \param cam_id camera id
    * \param time current local time
    * \param x observation x position
    * \param y observation y position
    *
    * insert to sqlite database.
    */
    void insert(int cam_id, std::string time, int x, int y);
    ///disconnect from sqlite database
    void disconnect();

private:
    ///private default constructor
    SqlConnector();
    ///singleton instance pointer
    static SqlConnector* instance;
    ///QT class that represents a connection to a database
    QSqlDatabase db;
};
#endif