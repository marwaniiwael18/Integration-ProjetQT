#include "employee.h"

Employee::Employee()
{
    ID=0;
    NOM=" ";
    PRENOM=" ";
    ADRESSE=" ";
    POSTE=" ";
    PASSWORD=" ";
    SALAIRE=0;
}
Employee::Employee(int ID,QString NOM,QString PRENOM,QString ADRESSE,QString POSTE,QString PASSWORD,int SALAIRE)
{
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->POSTE=POSTE;
    this->SALAIRE=SALAIRE;
    this->PASSWORD=PASSWORD;
}
/**************************************/
int Employee::getid() {  return ID; }
QString Employee::getnom() { return NOM; }
QString Employee::getprenom() { return PRENOM; }
QString Employee::getadresse() { return ADRESSE; }
QString Employee::getposte() { return POSTE; }
int Employee::getsalaire() {  return SALAIRE; }
/**************************************/
void Employee::setid(int ID) { this->ID=ID; }
void Employee::setnom(QString NOM) { this->NOM=NOM; }
void Employee::setprenom(QString PRENOM) { this->PRENOM=PRENOM; }
void Employee::setadresse(QString ADRESSE) { this->ADRESSE=ADRESSE; }
void Employee::setposte(QString POSTE) { this->POSTE=POSTE; }
void Employee::setsalaire(int SALAIRE) { this->SALAIRE=SALAIRE; }
/**************************************/
bool Employee::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(ID);
    query.prepare("INSERT INTO EMPLOYEES(ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE,PASSWORD)" "VALUES (:ID,:NOM,:PRENOM,:ADRESSE,:POSTE,:SALAIRE,:PASSWORD)");
    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":SALAIRE", SALAIRE);
    query.bindValue(":PASSWORD", PASSWORD);
    return query.exec();
}
bool Employee::supprimer(int ID)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYEES where ID= :ID");
    query.bindValue(":ID", ID);
    return query.exec();
}
bool Employee::modifier(int ID)
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEES SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, POSTE=:POSTE, PASSWORD=:PASSWORD, SALAIRE=:SALAIRE WHERE ID=:ID ");
    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":SALAIRE", SALAIRE);
    return query.exec();
}

QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE FROM EMPLOYEES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    return  model;
}

QSqlQueryModel * Employee ::rechercher(QString valeur)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYEES WHERE ID LIKE :valeur or NOM LIKE :valeur or PRENOM LIKE :valeur or ADRESSE LIKE :valeur or POSTE LIKE :valeur or SALAIRE LIKE :valeur");
    valeur = "%"+valeur+"%";

    //bindValue() de l'objet QSqlQuery est utilisée pour remplacer les marqueurs de position dans la requête SQL par la valeur de la chaîne de caractères "valeur".
    query.bindValue(":valeur",valeur);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Employee ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID from EMPLOYEES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return model;
}

QSqlQueryModel * Employee::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE from EMPLOYEES order by ID");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    return model;
}
QSqlQueryModel * Employee::tri_poste()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE from EMPLOYEES order by POSTE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    return model;
}
QSqlQueryModel * Employee::tri_salire()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE from EMPLOYEES order by SALAIRE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("SALAIRE"));
    return model;
}
void Employee::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
void Employee::chercheID(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EMPLOYEES where regexp_like(ID,:ID);");
    query->bindValue(":ID",x);
    if(x==0)
    {
        query->prepare("select * from EMPLOYEES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
void Employee::chercheNom(QTableView *table, QString x)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery *query =new QSqlQuery;
    query->prepare("select * from EMPLOYEES where regexp_like(NOM,:NOM);");
    query->bindValue(":NOM",x);
    if(x==0)
    {
        query->prepare("select * from EMPLOYEES;");
    }
    query->exec();
    model->setQuery(*query);
    table->setModel(model);
    table->show();
}
