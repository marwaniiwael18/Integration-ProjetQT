#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QApplication>



class Equipement
{
public:
  Equipement();
  Equipement(int,int,QString,QString);
  int getid();int getdateA();
  QString getnomE();
  QString getstatut();
  void setid(int);
  void setdateA(int);
  void setnomE(QString);
  void setstatut(QString);
  bool ajouter();
  QSqlQueryModel *afficher();
  bool supprimer(int);

  bool rechercher(int id);
  bool modifier(int);

  QSqlQueryModel *chercher(int);
  QSqlQueryModel * rechercher(QString valeur);
  QSqlQueryModel * triID();
  QSqlQueryModel * triNOM();
  QSqlQueryModel * triIDdesc();
  QSqlQueryModel * triNOMdesc();

private:
    int id,dateA;
    QString nomE ,statut;
};

#endif // EQUIPEMENT_H

