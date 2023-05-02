#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>

class Employee
{
public:
    Employee();
    Employee(int,QString,QString,QString,QString,QString,int);

    int getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getposte();
    int getsalaire();

    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setposte(QString);
    void setsalaire(int);

    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * rechercher(QString valeur);

    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* tri_salire();
    QSqlQueryModel* tri_poste();
    QSqlQueryModel* tri_nom();

    void clearTable(QTableView * table);
    void chercheID(QTableView *table, QString x);
    void chercheNom(QTableView *table, QString x);
    QString PASSWORD;
private:
    int ID;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString POSTE;
    int SALAIRE;

};

#endif // EMPLOYEE_H
