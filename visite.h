#ifndef VISITE_H
#define VISITE_H
#include <QString>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>



class Visite
{
public:
  Visite();
  Visite(int,int,int,int,QString);

  //Getters
  int getid();
  int getdatevisite();
  int getkilometrage();
  int getprixvisite();
  QString getresultat();


  //Setters
  void setid(int);
  void setdatevisite(int);
  void setkilometrage(int);
  void setprixvisite(int);
  void setresultat(QString);


  //Les fonctions
  bool ajouter();
  QSqlQueryModel *afficher();
  bool supprimer(int);
  // Déclaration de la méthode rechercher
  bool modifier(int);
  bool rechercher(int);
  //QSqlQueryModel *chercher(int);
  QSqlQueryModel * rechercher(QString);

 // QSqlQueryModel * rechercher(QString valeur);
  QSqlQueryModel * triID();
  QSqlQueryModel * triNOM();
  QSqlQueryModel * triIDdesc();
  QSqlQueryModel * triNOMdesc();





private:
    int id,datevisite,kilometrage,prixvisite;
    QString resultat;
};



#endif // VISITE_H
