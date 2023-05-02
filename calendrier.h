#ifndef CALENDRIER_H
#define CALENDRIER_H

#include <QDate>
#include <QDateTime>
#include <QMainWindow>
#include<QSqlQueryModel>


//! [0]


#include <QMainWindow>



QT_BEGIN_NAMESPACE
class QTextBrowser;
QT_END_NAMESPACE

class Calendrier : public QMainWindow
{
    Q_OBJECT

public:
     Calendrier();

public slots:
    void setFontSize(int size);
    void setMonth(int month);
    void setYear(QDate date);

private:
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;
};

#endif // CALENDRIER_H
