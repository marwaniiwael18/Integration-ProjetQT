
#include "visite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QVariant>
#include<QMessageBox>
#include <QApplication>


Visite::Visite()
{
id=0; datevisite=0;kilometrage=0;prixvisite=0;
resultat=" ";
}

Visite::Visite(int id,int datevisite,int kilometrage,int prixvisite,QString resultat)
{
    this->id=id;
    this->datevisite=datevisite;
    this->kilometrage=kilometrage;
    this->prixvisite=prixvisite;
    this->resultat=resultat;

}
//Getters
int Visite::getid(){return id;}
int Visite::getdatevisite(){return datevisite;}
int Visite::getkilometrage(){return kilometrage;}
int Visite::getprixvisite(){return prixvisite;}
QString Visite::getresultat(){return resultat;}


//Setters
void Visite::setid(int id){this->id=id;}
void Visite::setdatevisite(int datevisite){this->datevisite=datevisite;}
void Visite::setkilometrage(int kilometrage){this->kilometrage=kilometrage;}
void Visite::setprixvisite(int prixvisite){this->prixvisite=prixvisite;}
void Visite::setresultat(QString resultat){this->resultat=resultat;}

bool Visite::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO visite (id, datevisite, kilometrage, prixvisite, resultat) "
                  "VALUES (:id, :datevisite, :kilometrage, :prixvisite, :resultat)");
    query.bindValue(":id", id);
    query.bindValue(":datevisite", datevisite);
    query.bindValue(":kilometrage", kilometrage);
    query.bindValue(":prixvisite", prixvisite);
    query.bindValue(":resultat", resultat);

    //exec() envoie la requete pour l'exécuter
    return query.exec();

}


QSqlQueryModel* Visite::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();


         model->setQuery("SELECT* FROM visite");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("datevisite"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("kiloetrage"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixvisite"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("resultat"));


   return model;
   }
bool Visite::supprimer(int id)
{
    QSqlQuery query;
    query.prepare(" Delete from visite where id=:id");
    query.bindValue(0, id);

     return query.exec();
}
/*
bool Visite::rechercher(int id)
{
    // Requête SQL pour récupérer les informations du véhicule avec l'identifiant id
    QSqlQuery query;
    query.prepare("SELECT * FROM visite WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.first()) {
        // Si le véhicule est trouvé, on met à jour les attributs de l'objet courant
        this->setid(query.value("id").toInt());
        this->setdatevisite(query.value("datevisite").toDouble());
        this->setkilometrage(query.value("kilometrage").toDouble());
        this->setprixvisite(query.value("prixvisite").toDouble());
        this->setresultat(query.value("resultat").toString());

        return true;
    }
    return false;
}

*/
QSqlQueryModel * Visite::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("select * from visite where id LIKE '"+rech+"%'");
    return model;
}

bool Visite::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE visite SET id=:id, datevisite=:datevisite, kilometrage=:kilometrage, prixvisite=:prixvisite, resultat=:resultat  WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":datevisite", datevisite);
    query.bindValue(":kilometrage", kilometrage);
    query.bindValue(":prixvisite", prixvisite);
    query.bindValue(":resultat", resultat);

    return query.exec();
}


QSqlQueryModel * Visite::triID()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from visite order by ID ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datevisite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("kilometrage"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixvisite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("resultat"));


    return model;
}
QSqlQueryModel * Visite::triNOM()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from visite order by NOM ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datevisite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("kilometrage"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixvisite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("resultat"));


    return model;
}
QSqlQueryModel * Visite::triIDdesc()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from visite order by ID desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datevisite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("kilometrage"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixvisite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("resultat"));


    return model;
}
QSqlQueryModel * Visite::triNOMdesc()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from visite order by NOM desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("datevisite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("kilometrage"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prixvisite"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("resultat"));


    return model;
}










