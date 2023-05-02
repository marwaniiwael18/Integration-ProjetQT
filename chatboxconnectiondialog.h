#ifndef CHATBOXCONNECTIONDIALOG_H
#define CHATBOXCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class chatboxconnectiondialog;
}
class chatboxconnectiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit chatboxconnectiondialog(QWidget *parent = nullptr);
    ~chatboxconnectiondialog();
QString hostname() const;
quint16 port() const;
private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::chatboxconnectiondialog *ui;
    QString nHostname;
    quint16 nPort;
};
inline QString chatboxconnectiondialog::hostname() const
{
    return nHostname;
}
inline quint16 chatboxconnectiondialog::port() const
{
    return nPort;
}


#endif // CHATBOXCONNECTIONDIALOG_H
