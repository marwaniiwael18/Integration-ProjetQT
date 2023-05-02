#ifndef PISTE_H
#define PISTE_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QApplication>

class Piste
{
    public:
        Piste();
        Piste(int, int, int, int, QString);

        //Getters
        int getid();
        int getnumPiste();
        int getlongueur();
        int getlargeur();
        QString gettype();

        //Setters
        void setid(int);
        void setnumPiste(int);
        void setlongueur(int);
        void setlargeur(int);
        void settype(QString);

        //Fonctionnalités de base relatives à l'entité Piste
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        QSqlQueryModel * rechercher(QString valeur);
        QSqlQueryModel * triID();
        QSqlQueryModel * triIDdesc();
        QSqlQueryModel * trinumPiste();
        QSqlQueryModel * trinumPistedesc();
        QSqlQueryModel * tritype();
        QSqlQueryModel * tritypedesc();


    private:
        int id;
        int numPiste;
        int longueur;
        int largeur;
        QString type;

};

#endif // PISTE_H
