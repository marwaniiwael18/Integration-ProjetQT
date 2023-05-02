#ifndef RESERVATION_H
#define RESERVATION_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QApplication>
#include<QDateTime>
#include <QWidget>
#include<QDate>


class Reservation
{
    public:
        Reservation();
        Reservation(int,QString ,QString ,QString,int,QDateTime);


        //Getters
        int getid();
        QString getnom();
       QString getprenom();
       QString gettype_immatriculation();
        int getnumImmatriculation();
        QDateTime getdate_res();


        //Setters
        void setid(int);
        void setnom(QString);
        void setprenom(QString);
        void settype_immatriculation(QString);
        void setnumImmatriculation(int);
        void setdate_res(QDateTime );

        //Fonctionnalités de base relatives à l'entité Reservation
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int );

        QSqlQueryModel * rechercher(QString valeur);
        QSqlQueryModel * triID();
        QSqlQueryModel * triIDdesc();

        bool ajouter_historique(QString type,int numImmatriculation,int id);
          QSqlQueryModel * afficher_historique0();
        QSqlQueryModel * afficher_historique(QString type);


    private:
        int id;
        QString nom;
        QString prenom;
        QString type_immatriculation ;
        int numImmatriculation;
        QDateTime date_res;
};

#endif // RESERVATION_H
