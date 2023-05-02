#ifndef EMPLOYEES_STATISTIQUES_H
#define EMPLOYEES_STATISTIQUES_H

#include <QDialog>
#include "QtPrintSupport"
namespace Ui {
class Employees_Statistiques;
}

class Employees_Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Employees_Statistiques(QWidget *parent = nullptr);
    ~Employees_Statistiques();

private slots:
    void on_Empl_push_reture_clicked();

private:
    Ui::Employees_Statistiques *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // EMPLOYEES_STATISTIQUES_H
