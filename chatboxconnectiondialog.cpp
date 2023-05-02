#include "chatboxconnectiondialog.h"
#include "ui_chatboxconnectiondialog.h"

chatboxconnectiondialog::chatboxconnectiondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatboxconnectiondialog)
{
    ui->setupUi(this);
}
chatboxconnectiondialog::~chatboxconnectiondialog()
{
    delete ui;
}
void chatboxconnectiondialog::on_ok_clicked()
{
    nHostname = ui->hostname->text();
    nPort = ui->port->value();
    accept();
}
void chatboxconnectiondialog::on_cancel_clicked()
{
    reject();
}
