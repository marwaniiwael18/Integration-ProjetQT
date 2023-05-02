#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class connection
{
public:
    connection();
    bool CreateConnexion();
    bool OuvrirConnexion();
    void FermerConnexion();
    QSqlDatabase db;
};

#endif // CONNECTION_H
