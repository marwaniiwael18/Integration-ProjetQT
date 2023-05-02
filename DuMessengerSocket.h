#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H
#include <QTcpSocket>
class DuMessengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    DuMessengerSocket(qintptr handle,QObject *parent=nullptr);
signals:
    void DuReadyRead(DuMessengerSocket *);
    void DuStateChanged(DuMessengerSocket *, int);
};
#endif // DUMESSENGERSOCKET_H
