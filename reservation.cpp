#include "reservation.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QMessageBox>
#include <QApplication>
#include<QObject>
#include<QDateTimeEdit>
#include<QSqlQueryModel>


Reservation::Reservation()
{
    id=0;
    nom="";
    prenom="";
    type_immatriculation="";
    numImmatriculation=0;



}

Reservation::Reservation(int id, QString nom, QString prenom, QString type_immatriculation, int numImmatriculation, QDateTime date_res)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->type_immatriculation=type_immatriculation;
    this->numImmatriculation=numImmatriculation;
    this->date_res=date_res;
}

//Getters
int Reservation::getid(){return id;}
QString Reservation::getnom(){return nom;}
QString Reservation::getprenom(){return prenom;}
QString Reservation::gettype_immatriculation(){return type_immatriculation;}
int Reservation::getnumImmatriculation(){return numImmatriculation;}
QDateTime Reservation::getdate_res(){return date_res;}

//Setters
void Reservation::setid(int id){this->id=id;}
void Reservation::setnom(QString nom){this->nom=nom;}
void Reservation::setprenom(QString prenom){this->prenom=prenom;}
void Reservation::settype_immatriculation(QString type_immatriculation){this->type_immatriculation=type_immatriculation;}
void Reservation::setnumImmatriculation(int numImmatriculation){this->numImmatriculation=numImmatriculation;}
void Reservation::setdate_res(QDateTime date_res){this->date_res=date_res;}

bool Reservation::ajouter()
{
    QSqlQuery query;
    //QSqlQuery query2;// Requete d'ajout sur table HISEV

    QString res = QString::number(id);

    //prepare() prend la requete en parametre pour la preparer à l'exécution
    query.prepare("insert into Reservation(id, nom, prenom, type_immatriculation, numImmatriculation, date_res)" "values(:id, :nom, :prenom, :type_immatriculation, :numImmatriculation, :date_res )");
    //query2.prepare("insert into HISEV (nom_HIS,prenom_HIS,numImmatriculation_HIS,type_immatriculation,id_HIS)""values (:nom_HIS,:prenom_HIS,:numImmatriculation_HIS,:id_HIS,'UPDATED')");


    //Création des variables liées
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":type_immatriculation",type_immatriculation);
    query.bindValue(":numImmatriculation",numImmatriculation);
    query.bindValue(":date_res",date_res);




    return query.exec();
}



QSqlQueryModel* Reservation::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    //afficher le tableau
    model->setQuery("SELECT* FROM Reservation");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_immatriculation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("numImmatriculation"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_res"));


    return model;
}

/////////////////////////////// fin d'implementation des crud  /////////////////////////////////




bool Reservation::supprimer(int id)
{
    QSqlQuery query;

    //prepare() prend la requete en parametre pour la preparer à l'exécution
    query.prepare("Delete from Reservation where id=:id");

    //Création des variables liées
    query.bindValue(":id",id);



    //exec() envoie la requete pour l'exécuter
    return query.exec();
}
bool Reservation::modifier(int id)
{

QSqlQuery query;// Requete d'ajout sur table RESERVATION



query.prepare("UPDATE reservation SET nom=:nom,prenom=:prenom,numImmatriculation=:numImmatriculation,type_immatriculation=:type_immatriculation,date_res=:date_res, WHERE id=:id;");

     query.bindValue(":id",id);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":type_immatriculation",type_immatriculation);
     query.bindValue(":numImmatriculation", numImmatriculation );
     query.bindValue(":date_res",date_res);



             return query.exec();


     }



QSqlQueryModel* Reservation::rechercher(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM reservation WHERE id LIKE :valeur or nom LIKE :valeur or prenom LIKE :valeur or numImmatriculation LIKE :valeur or type_immatriculation LIKE :valeur");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}
QSqlQueryModel * Reservation::triID()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from Reservation order by ID ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_immatriculation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("numImmatriculation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_res"));

    return model;
}

QSqlQueryModel * Reservation::triIDdesc()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from Reservation order by ID desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_immatriculation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("numImmatriculation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("date_res"));

    return model;
}




//histo
bool Reservation::ajouter_historique(QString type,int numImmatriculation,int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("INSERT INTO history (id,type,numImmatriculation,date_historique)"
                  "VALUES (:id, :type, :numImmatriculation, :date_historique)");
    query.bindValue(":id", id);
        query.bindValue(":type", type);
        query.bindValue(":numImmatriculation", numImmatriculation);
            query.bindValue(":date_historique",  QDateTime::currentDateTime());
    return
            query.exec();
}

QSqlQueryModel * Reservation::afficher_historique0()
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * FROM history");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("numImmatriculation"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("date d'historique"));




    return model;
    }
QSqlQueryModel * Reservation::afficher_historique(QString type)
{
    QSqlQueryModel * model= new QSqlQueryModel();

         QString a=type;

         if(a=="tout")

         {        model->setQuery("select * FROM history");

             model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr("numImmatriculation"));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("date d'historique"));


         }

         else{

            model->setQuery("select * FROM history  WHERE nom LIKE '%"+a+"%'  ");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("numImmatriculation"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("date d'historique"));

}

    return model;
}

