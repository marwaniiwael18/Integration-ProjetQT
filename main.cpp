#include "mainwindow.h"
#include "widget.h"
#include "DuMessengerServer.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Widget d;
    d.resize(200,80);
    d.show();

    connection c;
    w.show();
    bool test=c.CreateConnexion();
    if(test)
            {w.show();
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("connection successful.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

        }
            else
                QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                            QObject::tr("connection failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
    DuMessengerServer Server;
    if(!Server.startServer(3333)){
    qDebug()<<"error:" << Server.errorString();
    return 1;
    }
    qDebug() << "Server started ...";
    return a.exec();
}

