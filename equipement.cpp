
#include "equipement.h"

#include<QSqlQuery>
#include<QtDebug>
#include<QMessageBox>
#include <QApplication>
#include<QObject>


Equipement::Equipement()
{
    id=0;
    dateA=0;
    nomE=" ";
    statut=" ";
}

Equipement::Equipement(int id,int dateA,QString nomE,QString statut)
{this->id=id; this->dateA=dateA; this->nomE=nomE; this->statut=statut;}
int Equipement::getid(){return id;}
int Equipement::getdateA(){return dateA;}
QString Equipement::getnomE(){return nomE;}
QString Equipement::getstatut(){return statut;}
void Equipement::setid(int id){this->id=id;}
void Equipement::setdateA(int dateA){this->dateA=dateA;}
void Equipement::setnomE(QString nomE){this->nomE=nomE;}
void Equipement::setstatut(QString statut){this->statut=statut;}

bool Equipement::ajouter()
{
     QSqlQuery query;

     QString id_string=QString::number(id);
     QString dateA_string=QString::number(dateA);

     //prepare() prend la requete en parametre pour la preparer à l'exécution
     query.prepare("insert into Equipement(id, nomE, dateA, statut)" "values(:id, :nomE, :dateA, :statut)");

     //Création des variables liées
     query.bindValue(":id",id_string);
     query.bindValue(":dateA", dateA_string);
     query.bindValue(":nomE", nomE);
     query.bindValue(":statut", statut);

     //exec() envoie la requete pour l'exécuter
     return query.exec();
}

bool Equipement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare(" Delete from Equipement where id=:id");
    query.bindValue(0, id);

     return query.exec();
}

QSqlQueryModel* Equipement::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();


         model->setQuery("SELECT* FROM Equipement");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'achat"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'equipement"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("statut"));

   return model;
}

bool Equipement::rechercher(int id)
{
    // Requête SQL pour récupérer les informations du Equipement avec l'identifiant id
    QSqlQuery query;
    query.prepare("SELECT * FROM Equipement WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.first()) {
        // Si l'equipement est trouvé, on met à jour les attributs de l'objet courant
        this->setid(query.value("id").toInt());
          this->setdateA(query.value("date d'achat").toInt());
        this->setnomE(query.value("nom d'equipement").toString());
        this->setstatut(query.value("statut").toString());


        return true;
    }
    return false;
}

bool Equipement::modifier(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE Equipement SET id=:id, dateA=:dateA, nomE=:nomE, statut=:statut,  WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":dateA", dateA);
    query.bindValue(":nomE", nomE);
    query.bindValue(":statut", statut);
    return query.exec();
}
QSqlQueryModel* Equipement::rechercher(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM equipement WHERE id LIKE :valeur or dateA LIKE :valeur or nomE LIKE :valeur or statut LIKE :valeur ");
    valeur = "%"+valeur+"%";
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel * Equipement::triID()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from equipement order by ID ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'achat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'equipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("statut"));

    return model;
}
QSqlQueryModel * Equipement::triNOM()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from equipement order by NOME ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'achat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'equipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("statut"));

    return model;
}
QSqlQueryModel * Equipement::triIDdesc()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from equipement order by ID desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'achat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'equipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("statut"));

    return model;
}
QSqlQueryModel * Equipement::triNOMdesc()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * from equipement order by NOME desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date d'achat"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'equipement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("statut"));

    return model;
}
