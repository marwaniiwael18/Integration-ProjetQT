#include "ardBarriere.h"
#include "ardPorte.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include "piste.h"
#include "captchabox.h"
#include "vehicule.h"
#include "qrcode.h"
#include"smtp.h"
#include "equipement.h"
#include "exportexcelobject.h"
#include "chatboxconnectiondialog.h"
#include "reservation.h"
#include "calendrier.h"
#include "visite.h"
#include "notifications.h"

#include <QMessageBox>
#include <QApplication>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QTcpSocket>
#include <QTextStream>
#include<QIntValidator>
#include <QPrinter>
#include "QDebug"
#include "QStringList"
#include <QtWidgets>
#include <QString>
#include <QVector>
#include <stdlib.h>
#include <QTextCursor>
#include <QFileDialog>
#include <QTextDocument>
#include <QDate>
#include <QtSql>
#include <QtCharts>
#include <QtGui>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QChart>
#include<QString>
#include<QStatusBar>
#include <QSound>
#include<QTimer>
#include<QDateTime>
#include <QPixmap>
#include <QTabWidget>
#include <QObject>
#include <QDialog>
#include <QValidator>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSequentialAnimationGroup>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>

#include <QTcpSocket>
#include <QTextStream>
#include<QIntValidator>
#include <QPrinter>
#include "QDebug"
#include "QStringList"
#include <QtWidgets>
#include <QString>
#include <QVector>
#include <stdlib.h>
#include <QTextCursor>
#include <QFileDialog>
#include <QTextDocument>
#include <QDate>
#include <QtSql>
#include <QtCharts>
#include <QtGui>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QChart>
#include<QStatusBar>
#include <QSound>
#include<QTimer>
#include<QDateTime>
#include<QMediaPlayer>
#include <QDataStream>
#include <QPrintDialog>
#include <QSqlQuery>
#include<QComboBox>
#include<QSaveFile>
#include<QBuffer>
#include <QSqlQueryModel>
#include<QLineSeries>
#include<QUrl>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include "mainwindow.h"
#include<QGraphicsView>
#include<QSystemTrayIcon>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QItemSelectionModel>
#include <QDesktopWidget>
#include <QDateEdit>




using namespace QrCodegen;
QString days="";
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->leid_2->setValidator(new QIntValidator(0, 9999999, this));

    ui->tab_reservation->setModel(R.afficher());
    ui->tableView_his->setModel(R.afficher_historique0());


    //arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).




    /******* LOGIN *******/
    ui->Login_line_ID->setValidator( new QIntValidator(0, 99999999, this));
    ui->stackedWidget->setCurrentIndex(0);
    ui->Menu_push_Employees->setDisabled(true);
    ui->Menu_push_Pistes->setDisabled(true);
    ui->Menu_push_Visits->setDisabled(true);
    ui->Menu_push_Vehicules->setDisabled(true);
    ui->Menu_push_Equipements->setDisabled(true);
    ui->Menu_push_Reservations->setDisabled(true);

    /******* GESTION EMPLOYEE *******/
    ui->Empl_line_Salaire->setValidator( new QIntValidator(0, 99999999, this));
    //ui->Empl_combo_ID->setModel(E.afficher_id());
    ui->tableView->setModel (E.afficher());
    nSocket=new QTcpSocket(this);
    connect(nSocket,&QTcpSocket::readyRead,[&](){
        QTextStream T(nSocket);
        auto text=T.readAll();
        ui->Empl_text_Chatbox->append(text);
    });


 /*
  /////////////////////////////Piste///////////////////////////////////////////////////////////
  */

    //condition pour la valeur de l'id
        ui->le_id_2->setValidator(new QIntValidator(0, 9999999, this));
        ui->tab_piste->setModel(P.afficher());

        //maps

        //QSettings::IniFormat : Le format de stockage des paramètres (format INI)
        //QSettings::UserScope : Le domaine de portée des paramètres (les paramètres sont stockés pour l'utilisateur actuel)
        //QCoreApplication::organizationName() : Le nom de l'organisation de l'application
        //QCoreApplication::applicationName() : Le nom de l'application
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());

        ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");


        //music
        // Configuration du tableau de liste de lecture
        m_playListModel = new QStandardItemModel(this);
        ui->playlistView->setModel(m_playListModel);    // Définition du modèle de données dans le TableView

        // Définition des en-têtes de tableau
        m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")
                                                                << tr("File Path"));
        ui->playlistView->hideColumn(1);    // Masquer la colonne qui stocke le chemin d'accès au fichier
        ui->playlistView->verticalHeader()->setVisible(false);                  // Masquer les numéros de ligne
        ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Activer la surbrillance des lignes
        ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Nous n'autorisons qu'une seule ligne à sélectionner
        ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Désactiver l'édition

        // Activer la dernière colonne visible pour s'adapter à la largeur de TableView
        ui->playlistView->horizontalHeader()->setStretchLastSection(true);

        m_player = new QMediaPlayer(this);          // Initialisation du lecteur
        m_playlist = new QMediaPlaylist(m_player);  // Initialisation de la liste de lecture
        m_player->setPlaylist(m_playlist);          // Installer la liste de lecture dans le lecteur
        m_player->setVolume(70);                    // Régler le volume de lecture des pistes
        m_playlist->setPlaybackMode(QMediaPlaylist::Loop);  // Définir la liste de lecture en boucle

        // connecter les boutons de commande aux fentes de contrôle
        // Ici, notez que la navigation dans la playlist s'effectue à travers la playlist
        // et démarrer / mettre en pause / arrêter via le lecteur lui-même
        connect(ui->btn_previous, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
        connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);
        connect(ui->btn_play, &QToolButton::clicked, m_player, &QMediaPlayer::play);
        connect(ui->btn_pause, &QToolButton::clicked, m_player, &QMediaPlayer::pause);
        connect(ui->btn_stop, &QToolButton::clicked, m_player, &QMediaPlayer::stop);

        // Lorsque vous double-cliquez sur une piste dans le tableau, définissez la piste dans la liste de lecture
        connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
            m_playlist->setCurrentIndex(index.row());
        });

        // lors de la modification de l'index de la piste actuelle dans la liste de lecture, définissez le nom du fichier dans une étiquette spéciale
        connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
            ui->currentTrack->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
        });

 /*
    //////////////////////////////vehicule//////////////////////////////////////////////////////////////
  */

    ui->leid->setValidator( new QIntValidator(0, 9999999, this));
    ui->kilometrage->setValidator( new QIntValidator(0, 9999999, this));
    ui->NumS->setValidator( new QIntValidator(0, 9999999, this));
    ui->leid->setValidator( new QIntValidator(0, 9999999, this));
    ui->kilometrage->setValidator( new QIntValidator(0, 9999999, this));
    ui->NumS->setValidator( new QIntValidator(0, 9999999, this));

    ui->tableView_2->setModel(v.afficher());

m_currentPage = 0;


/*
   //////////////////////////////equipement//////////////////////////////////////////////////////////////
 */


    ui->leid->setValidator( new QIntValidator(0, 9999999, this));
    ui->dateaa->setValidator( new QIntValidator(0, 9999999, this));

    ui->tabequipement->setModel(E.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
       connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));





/*
 ///////////////////////////VISITES//////////////////////////////////////
 */
       ui->le_datevisite->setValidator( new QIntValidator(0, 9999999, this));
       ui->le_kilometrage->setValidator( new QIntValidator(0, 9999999, this));
       ui->le_prixvisite->setValidator( new QIntValidator(0, 9999999, this));

       ui->tab_visite->setModel(v.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Login_push_Login_clicked()
{
    QString ID = ui->Login_line_ID->text();
    QString PASSWORD = ui->Login_line_MDP->text();
    QSqlQuery query;
    QString poste;
    if(query.exec("SELECT * from EMPLOYEES where ID='"+ID+"' and PASSWORD='"+PASSWORD+"'" ))
    {
        if (query.next())
        {
            poste=query.value(4).toString();

            ui->stackedWidget->setCurrentIndex(1);
            if (poste.compare("Administrateur")==0){
                ui->Menu_push_Employees->setEnabled(true);
                ui->Menu_push_Pistes->setEnabled(true);
                ui->Menu_push_Visits->setEnabled(true);
                ui->Menu_push_Vehicules->setEnabled(true);
                ui->Menu_push_Equipements->setEnabled(true);
                ui->Menu_push_Reservations->setEnabled(true);
            }
            if (poste.compare("Employees")==0){
                ui->Menu_push_Employees->setEnabled(true);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Pistes")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(true);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Visits")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(true);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Vehicules")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(true);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Equipements")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(true);
                ui->Menu_push_Reservations->setEnabled(false);
            }
            if (poste.compare("Reservations")==0){
                ui->Menu_push_Employees->setEnabled(false);
                ui->Menu_push_Pistes->setEnabled(false);
                ui->Menu_push_Visits->setEnabled(false);
                ui->Menu_push_Vehicules->setEnabled(false);
                ui->Menu_push_Equipements->setEnabled(false);
                ui->Menu_push_Reservations->setEnabled(true);
            }
            QString NOM=query.value(1).toString();
            QString PRENOM=query.value(2).toString();
            ui->Login_lebel_Info->setText("Connecté: "+NOM+" "+PRENOM+"");
            ui->Menu_label_info->setText("Logged in as: "+NOM+" "+PRENOM+"\nGestion: "+poste+"");
        }
        else
        {
            ui->Login_lebel_Info->setText("ID/Mot de passe incorrect");
        }
    }
}

void MainWindow::on_Menu_push_Employees_clicked(){ui->stackedWidget->setCurrentIndex(2);}
void MainWindow::on_Menu_push_Vehicules_clicked(){ui->stackedWidget->setCurrentIndex(3);}
void MainWindow::on_Menu_push_Visits_clicked(){ui->stackedWidget->setCurrentIndex(4);}
void MainWindow::on_Menu_push_Reservations_clicked(){ui->stackedWidget->setCurrentIndex(5);}
void MainWindow::on_Menu_push_Equipements_clicked(){ui->stackedWidget->setCurrentIndex(6);}
void MainWindow::on_Menu_push_Pistes_clicked(){ui->stackedWidget->setCurrentIndex(7);}



void MainWindow::on_Menu_push_Reture_clicked(){ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::on_Menu_push_Quitter_clicked(){close();}




/*
 ////////////////////////////////////////////////////EMPLOYEES/////////////////////////////////////////////////////////////////////////////
 */

void MainWindow::on_Empl_push_Ajouter_clicked()
{
    // Vérification que tous les champs sont remplis
        if(ui->Empl_line_ID->text().isEmpty() || ui->Empl_line_Nom->text().isEmpty() || ui->Empl_line_Prenom->text().isEmpty() || ui->Empl_line_Adresse->text().isEmpty() ||
                ui->Empl_combo_Poste->currentText().isEmpty() || ui->Empl_line_MDP->text().isEmpty() || ui->Empl_line_Salaire->text().isEmpty())
        {
            QMessageBox::warning(nullptr, QObject::tr("Attention"), QObject::tr("Veuillez remplir tous les champs"));
            return;
        }

    //Récupération des informations saisies
    int ID=ui->Empl_line_ID->text().toInt();
    QString NOM=ui->Empl_line_Nom->text();
    QString PRENOM=ui->Empl_line_Prenom->text();
    QString ADRESSE=ui->Empl_line_Adresse->text();
    QString POSTE=ui->Empl_combo_Poste->currentText();
    QString PASSWORD=ui->Empl_line_MDP->text();
    int SALAIRE=ui->Empl_line_Salaire->text().toInt();

    //instancier un objet de la classe employee
    //en utilisant les informations saisies dans l'interface
    Employee E(ID,NOM,PRENOM,ADRESSE,POSTE,PASSWORD,SALAIRE);

    //insérer l'objet piste instancié dans la table employee
    //et récupérer la valeur de retour de query.exec()
    bool test=E.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres l'ajout
        ui->tableView->setModel(E.afficher());
        //ui->Empl_combo_ID->setModel (E.afficher_id());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_Empl_push_Modifier_2_clicked()
{
    //Récupération des informations saisies dans les champs
    int ID=ui->Empl_line_ID->text().toInt();
    QString NOM=ui->Empl_line_Nom->text();
    QString PRENOM=ui->Empl_line_Prenom->text();
    QString ADRESSE=ui->Empl_line_Adresse->text();
    QString POSTE=ui->Empl_combo_Poste->currentText();
    QString PASSWORD=ui->Empl_line_MDP->text();
    int SALAIRE=ui->Empl_line_Salaire->text().toInt();

    // Vérifier que l'identifiant saisi est valide
    if (ID <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return;
    }

    // Vérifier que les champs obligatoires sont remplis
    if (NOM <= 0 || PRENOM <= 0 || POSTE <= 0 || SALAIRE <= 0 || PASSWORD <= 0 || ADRESSE.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Vérifier que l'identifiant existe dans la table
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
        return;
    }
    if (!query.next())
    {
        QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
        return;
    }

    // Demander à l'utilisateur de confirmer la modification
    QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
        "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
        QMessageBox::Yes|QMessageBox::No);

    if (confirmUpdate == QMessageBox::No) {
        return; // L'utilisateur a annulé la modification, sortir de la fonction
    }

    // Exécuter la requête SQL pour mettre à jour l'enregistrement
    query.prepare("UPDATE EMPLOYEES SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, POSTE=:POSTE, PASSWORD=:PASSWORD, SALAIRE=:SALAIRE WHERE ID=:ID ");
    query.bindValue(":ID", ID);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":PASSWORD", PASSWORD);
    query.bindValue(":SALAIRE", SALAIRE);

    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Modification effectuée\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau après la modification
        ui->tableView->setModel(E.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Modification non effectuée\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_Empl_push_Supprimer_clicked()
{
    // Récupérer l'identifiant de l'enregistrement à supprimer
    int ID = ui->id_supp->text().toInt();

    if (ID <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return; // Sortir de la fonction si l'identifiant est invalide
    }

    // Vérifier si l'identifiant existe dans la table
    QSqlQuery query;

    query.prepare("SELECT * FROM EMPLOYEES WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
        return; // Sortir de la fonction en cas d'erreur de requête
    }
    if (!query.next())
    {
        QMessageBox::warning(this, "Attention", "L'identifiant à supprimer n'existe pas dans la table.");
        return; // Sortir de la fonction si l'identifiant n'existe pas dans la table
    }

    // Demander à l'utilisateur de confirmer la suppression
        QMessageBox::StandardButton confirmDelete = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir supprimer cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmDelete == QMessageBox::No) {
            return; // L'utilisateur a annulé la suppression, sortir de la fonction
        }

    Employee E1;
    E1.setid(ui->id_supp->text().toInt());

    bool test=E1.supprimer(E1.getid());

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Suppression effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres la suppression
        ui->tableView->setModel(E1.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Suppression non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_rechercher_clicked()
{
    // Récupérer la valeur de recherche et supprimer les espaces inutiles
        QString valeur = ui->Empl_line_Recherche->text().trimmed();

        // Vérifier si la valeur de recherche est vide
        if (valeur.isEmpty())
        {
            // Afficher un message d'erreur
            QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
            // Quitter la fonction sans exécuter la recherche
            return;
        }

        // Appeler la fonction de recherche dans la classe Piste et récupérer le modèle de résultats
        QSqlQueryModel *model = E.rechercher(valeur);

        // Vérifier si aucun résultat n'a été trouvé
        if (model->rowCount() == 0)
        {
            // Afficher un message d'information
            QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
        }
        else
        {
            // Créer un message avec le nombre de résultats trouvés
            QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
            // Afficher un message d'information avec le nombre de résultats trouvés
            QMessageBox::information(this, "Recherche", message);
            // Définir le modèle de résultats dans la table
            ui->tableView->setModel(model);
            // Trier les résultats par ordre croissant de l'id
            ui->tableView->sortByColumn(0, Qt::AscendingOrder);
        }
}

/*void MainWindow::on_Empl_combo_ID_currentIndexChanged(int)
{
    int id=ui->Empl_combo_ID->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYEES where ID='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->Empl_line_ID->setText(query.value(0).toString()) ;
            ui->Empl_line_Nom->setText(query.value(1).toString()) ;
            ui->Empl_line_Prenom->setText(query.value(2).toString()) ;
            ui->Empl_line_Adresse->setText(query.value(3).toString()) ;
            ui->Empl_combo_Poste->setCurrentText(query.value(4).toString()) ;
            ui->Empl_line_Salaire->setText(query.value(5).toString()) ;
            ui->Empl_line_MDP->setText(query.value(6).toString()) ;
        }
    }
    else
    {
        ui->Empl_label_GInfo->setText("Echec de chargement");
    }
}*/

void MainWindow::on_Empl_line_Recherche_textChanged(const QString &arg1)
{
    if (ui->Empl_radio_ID->isChecked()==true)
    {
        E.clearTable(ui->tableView);
        E.chercheID(ui->tableView,arg1);
    }
    if (ui->Empl_radio_Nom->isChecked()==true)
    {
        E.clearTable(ui->tableView);
        E.chercheNom(ui->tableView,arg1);
    }
}

void MainWindow::on_Empl_push_TriSalire_clicked()
{
    ui->Empl_label_TInfo->setText("Tri Salaire effectué");
    ui->tableView->setModel(E.tri_salire());
}

void MainWindow::on_Empl_push_TriPoste_clicked()
{
        ui->Empl_label_TInfo->setText("Tri Poste effectué");
        ui->tableView->setModel(E.tri_poste());
}

void MainWindow::on_Empl_push_TriNom_clicked()
{
    ui->Empl_label_TInfo->setText("Tri Nom effectué");
    ui->tableView->setModel(E.tri_nom());
}

void MainWindow::on_Empl_push_ExportPDF_clicked()
{
    QPdfWriter pdf("C:/Users/USER/Desktop/GestionEmployee/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(3000,1500,"LISTE DES EMPLOYEES");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    //painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"ID");
    painter.drawText(1800,3300,"NOM");
    painter.drawText(2800,3300,"PRENOM");
    painter.drawText(3800,3300,"ADRESSE");
    painter.drawText(5000,3300,"POSTE");
    painter.drawText(6900,3300,"SALAIRE");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select ID,NOM,PRENOM,ADRESSE,POSTE,SALAIRE from EMPLOYEES");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(2800,i,query.value(2).toString());
        painter.drawText(3800,i,query.value(3).toString());
        painter.drawText(4800,i,query.value(4).toString());
        painter.drawText(6700,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/USER/Desktop/GestionEmployee/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void MainWindow::on_Empl_push_Send_clicked()
{
    QTextStream T(nSocket);
    T << ui->Empl_line_Nickname-> text() << ": " << ui->Empl_line_Message->text();
    nSocket->flush();
    ui->Empl_line_Message->clear();
}

void MainWindow::on_Empl_push_Bind_clicked()
{
    chatboxconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {return;
    }
    nSocket->connectToHost(D.hostname(),D.port());
}

void MainWindow::on_Empl_push_Statistiques_clicked()
{
    stat = new Employees_Statistiques(this);
    stat->show();
}

void MainWindow::on_Empl_push_reture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




/*
////////////////////////////////////////////////////////////PISTES////////////////////////////////////////////////////////////////////////
*/


void MainWindow::on_Piste_push_reture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pb_ajouter_clicked()
{
    // Vérification que tous les champs sont remplis
        if(ui->le_id_2->text().isEmpty() || ui->le_numpiste_2->text().isEmpty() || ui->le_longueur_2->text().isEmpty() || ui->le_largeur_2->text().isEmpty() || ui->le_type_2->text().isEmpty())
        {
            QMessageBox::warning(nullptr, QObject::tr("Attention"), QObject::tr("Veuillez remplir tous les champs"));
            return;
        }

    //Récupération des informations saisies dans les 5 champs
    int id=ui->le_id_2->text().toInt();
    int numPiste=ui->le_numpiste_2->text().toInt();
    int longueur=ui->le_longueur_2->text().toInt();
    int largeur=ui->le_largeur_2->text().toInt();
    QString type=ui->le_type_2->text();

    //instancier un objet de la classe piste
    //en utilisant les informations saisies dans l'interface
    Piste P(id, numPiste, longueur, largeur, type);

    //insérer l'objet piste instancié dans la table piste
    //et récupérer la valeur de retour de query.exec()
    bool test=P.ajouter();

    //si la requete executée => QMessageBox::information
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres l'ajout
        ui->tab_piste->setModel(P.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_modifier_clicked()
{
    //Récupération des informations saisies dans les 5 champs
    int id=ui->le_id_2->text().toInt();
    int numPiste=ui->le_numpiste_2->text().toInt();
    int longueur=ui->le_longueur_2->text().toInt();
    int largeur=ui->le_largeur_2->text().toInt();
    QString type=ui->le_type_2->text();

    // Vérifier que l'identifiant saisi est valide
    if (id <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return;
    }

    // Vérifier que les champs obligatoires sont remplis
    if (numPiste <= 0 || longueur <= 0 || largeur <= 0 || type.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Vérifier que l'identifiant existe dans la table
    QSqlQuery query;
    query.prepare("SELECT * FROM piste WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
        return;
    }
    if (!query.next())
    {
        QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
        return;
    }

    // Demander à l'utilisateur de confirmer la modification
    QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
        "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
        QMessageBox::Yes|QMessageBox::No);

    if (confirmUpdate == QMessageBox::No) {
        return; // L'utilisateur a annulé la modification, sortir de la fonction
    }

    // Exécuter la requête SQL pour mettre à jour l'enregistrement
    query.prepare("UPDATE piste SET numPiste = :numPiste, longueur = :longueur, largeur = :largeur, type = :type WHERE id = :id");
    query.bindValue(":numPiste", numPiste);
    query.bindValue(":longueur", longueur);
    query.bindValue(":largeur", largeur);
    query.bindValue(":type", type);
    query.bindValue(":id", id);

    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Modification effectuée\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau après la modification
        ui->tab_piste->setModel(P.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Modification non effectuée\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_clicked()
{
    // Récupérer l'identifiant de l'enregistrement à supprimer
    int id = ui->id_supp->text().toInt();

    if (id <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return; // Sortir de la fonction si l'identifiant est invalide
    }

    // Vérifier si l'identifiant existe dans la table
    QSqlQuery query;

    query.prepare("SELECT * FROM piste WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
        return; // Sortir de la fonction en cas d'erreur de requête
    }
    if (!query.next())
    {
        QMessageBox::warning(this, "Attention", "L'identifiant à supprimer n'existe pas dans la table.");
        return; // Sortir de la fonction si l'identifiant n'existe pas dans la table
    }

    // Demander à l'utilisateur de confirmer la suppression
        QMessageBox::StandardButton confirmDelete = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir supprimer cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmDelete == QMessageBox::No) {
            return; // L'utilisateur a annulé la suppression, sortir de la fonction
        }

    Piste P1;
    P1.setid(ui->id_supp->text().toInt());

    bool test=P1.supprimer(P1.getid());

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Suppression effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres la suppression
        ui->tab_piste->setModel(P.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Suppression non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_rechercher_3_clicked()
{
    // Récupérer la valeur de recherche et supprimer les espaces inutiles
    QString valeur = ui->Empl_line_Recherche_3->text().trimmed();

    // Vérifier si la valeur de recherche est vide
    if (valeur.isEmpty())
    {
        // Afficher un message d'erreur
        QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
        // Quitter la fonction sans exécuter la recherche
        return;
    }

    // Appeler la fonction de recherche dans la classe Piste et récupérer le modèle de résultats
    QSqlQueryModel *model = P.rechercher(valeur);

    // Vérifier si aucun résultat n'a été trouvé
    if (model->rowCount() == 0)
    {
        // Afficher un message d'information
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
    }
    else
    {
        // Créer un message avec le nombre de résultats trouvés
        QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
        // Afficher un message d'information avec le nombre de résultats trouvés
        QMessageBox::information(this, "Recherche", message);
        // Définir le modèle de résultats dans la table
        ui->tab_piste->setModel(model);
        // Trier les résultats par ordre croissant de l'id
        ui->tab_piste->sortByColumn(0, Qt::AscendingOrder);
    }
}

void MainWindow::on_Empl_push_ExportPDF_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1450,"Liste Des Pistes");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 10));
    painter.drawText(300,3300,"ID");
    painter.drawText(1500,3300,"Num_piste");
    painter.drawText(3000,3300,"Longueur");
    painter.drawText(4800,3300,"Largeur");


    painter.drawRect(100,3000,9400,10700);

    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT * FROM vehicule");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(3000,i,query.value(2).toString());
        painter.drawText(4800,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8400,i,query.value(5).toString());
        painter.drawText(10000,i,query.value(6).toString());

        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }
}

void MainWindow::on_triID_clicked()
{
    ui->tab_piste->setModel(P.triID());
}

void MainWindow::on_ID_desc_clicked()
{
    ui->tab_piste->setModel(P.triIDdesc());
}

void MainWindow::on_triID_2_clicked()
{
    ui->tab_piste->setModel(P.trinumPiste());
}

void MainWindow::on_trinumPistedesc_clicked()
{
    ui->tab_piste->setModel(P.trinumPistedesc());
}

void MainWindow::on_tritype_clicked()
{
    ui->tab_piste->setModel(P.tritype());
}

void MainWindow::on_tritypedesc_clicked()
{
    ui->tab_piste->setModel(P.tritypedesc());
}

void MainWindow::on_pushButton_2_clicked()
{
    //Créer une instance de la classe QSqlQueryModel pour récupérer les données de la base de données.
    QSqlQueryModel * model= new QSqlQueryModel();

    //Exécuter une requête SQL pour récupérer le type de chaque piste de la table "piste".
    model->setQuery("SELECT type FROM piste ");
    //Obtenir le nombre de résultats retournés par la requête précédente et le stocker dans la variable e.
    float e=model->rowCount();
    //Exécuter une requête SQL pour récupérer le numéro de chaque piste de la table "piste".
    model->setQuery("SELECT numPiste FROM piste ");
    float ee=model->rowCount();

    //Calculer le nombre total de pistes en additionnant les variables e et ee.
    float total=e+ee;

    QString a=QString("type"+QString::number((e*100)/total,'f',2)+"%" );
    QString b=QString("numPiste"+QString::number((ee*100)/total,'f',2)+"%" );

    // Créer une instance de la classe QPieSeries pour stocker les données du graphique à secteurs.
    QPieSeries *series = new QPieSeries();

    series->append(a,e);
    series->append(b,ee);

    if (e!=0)
    {
        // Créer une instance de la classe QPieSeries pour stocker les données du graphique à secteurs.
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if ( ee!=0)
    {
         // Add label, explode and define brush for 2nd slice
         QPieSlice *slice1 = series->slices().at(1);
         //slice1->setExploded();
         slice1->setLabelVisible();
     }

     // Create the chart widget
     QChart *chart = new QChart();

     // Add data to chart with title and hide legend
     chart->addSeries(series);

     chart->setTitle("Pourcentage des types et numPiste : nombre total : "+ QString::number(total));
     chart->legend()->hide();

     // Used to display the chart
     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     chartView->resize(1000,500);
     chartView->show();
}

//MUSIC
void MainWindow::on_btn_add_clicked()
{
    // С помощью диалога выбора файлов делаем множественный выбор mp3 файлов
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3)"));

    // Далее устанавливаем данные по именам и пути к файлам
    // в плейлист и таблицу отображающую плейлист
    foreach (QString filePath, files)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
}

//captcha
void MainWindow::on_Empl_push_Statistiques_4_clicked()
{
    captchaBox = new CaptchaBox();
    captchaBox->setWindowTitle("Captcha");
    captchaBox->show();
}


/*
////////////////////////////////////////////////////////////VEHICULE////////////////////////////////////////////////////////////////////////
*/


/*void MainWindow::on_Piste_push_reture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}*/


void MainWindow::on_pb_ajouter_2_clicked()
{
    //Récupération des informations saisies dans les 5 champs
       int id=ui->leid->text().toInt();
       int kilometrage=ui->kilometrage->text().toInt();
       QString nom=ui->lenom->text();
       QString prenom=ui->leprenom->text();
       QString marque=ui->lamarque->text();
       QString modele=ui->lemodele->text();
       int NumSerie=ui->NumS->text().toInt();

       //instancier l'objet de la classe vehicule
       Vehicule V(id,kilometrage,prenom,nom,marque,modele,NumSerie);

    //insérer l'objet piste instancié dans la table piste
    //et récupérer la valeur de retour de query.exec()
    bool test=V.ajouter();

    //si la requete executée => QMessageBox::information
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres l'ajout
        ui->tableView_2->setModel(v.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}



void MainWindow::on_pb_supprimer_2_clicked()
{
    Vehicule v1;
    v1.setid(ui->id_supp->text().toInt());

    bool existe = v1.rechercher(v1.getid()); // Rechercher le véhicule

    if (existe) {
        // Demander une confirmation avant la suppression
        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer ce véhicule ?", QMessageBox::Yes | QMessageBox::No);
        if (confirmation == QMessageBox::Yes) {
            bool test = v1.supprimer(v1.getid()); // Supprimer le véhicule
            if (test) {
                QMessageBox::information(this, "Succès", "Suppression avec succès.");
                ui->tableView_2->setModel(v.afficher());
            } else {
                QMessageBox::warning(this, "Echec", "Echec de suppression.");
            }
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Le véhicule n'existe pas."); // Alerter l'utilisateur que le véhicule n'a pas été trouvé
    }
}

void MainWindow::on_pb_modifier_2_clicked()
{
    int id=ui->leid->text().toInt();
    int kilometrage=ui->kilometrage->text().toInt();
    QString nom=ui->lenom->text();
    QString prenom=ui->leprenom->text();
    QString marque=ui->lamarque->text();
    QString modele=ui->lemodele->text();
    int NumSerie=ui->NumS->text().toInt();


Vehicule V(id,kilometrage,nom,prenom,marque,modele,NumSerie);
bool test=V.modifier(id);
if(test){
ui->tableView_2->setModel(V.afficher());}
// Vérifier que l'identifiant saisi est valide
        if (id <= 0)
        {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
            return;
        }
        // Vérifier que les champs obligatoires sont remplis
            if (kilometrage <=0|| nom.isEmpty() ||prenom.isEmpty()|| marque.isEmpty() || modele.isEmpty()|| NumSerie <=0 )
            {
                QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
                return;
            }

        // Vérifier que l'identifiant existe dans la table
        QSqlQuery query;
        query.prepare("SELECT * FROM reservation WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
            return;
        }
        if (!query.next())
        {
            QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
            return;
        }

        // Demander à l'utilisateur de confirmer la modification
        QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmUpdate == QMessageBox::No) {
            return; // L'utilisateur a annulé la modification, sortir de la fonction
        }

        // Exécuter la requête SQL pour mettre à jour l'enregistrement

        query.prepare("UPDATE reservation SET kilometrage = :kilometrage, nom = :nom, prenom = :prenom ,marque = :marque, modele = :modele WHERE id = :id");
        query.bindValue(":id", id);
        query.bindValue(":kilometrage", kilometrage);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":marque", marque);
        query.bindValue(":modele", modele);
        query.bindValue(":NumSerie", NumSerie);


        if (query.exec())
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Modification effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);

            //Actualiser le tableau après la modification
            ui->tableView_2->setModel(V.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("Modification non effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_rechercher_clicked()
{
    // Récupérer la valeur de recherche et supprimer les espaces inutiles
    QString valeur = ui->lerechercher->text().trimmed();

    // Vérifier si la valeur de recherche est vide
    if (valeur.isEmpty())
    {
        // Afficher un message d'erreur
        QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
        // Quitter la fonction sans exécuter la recherche
        return;
    }

    // Appeler la fonction de recherche dans la classe Piste et récupérer le modèle de résultats
    QSqlQueryModel *model = v.rechercher(valeur);

    // Vérifier si aucun résultat n'a été trouvé
    if (model->rowCount() == 0)
    {
        // Afficher un message d'information
        QMessageBox::information(this, "Recherche", "AQucun résultat trouvé.");
    }
    else
    {
        // Créer un message avec le nombre de résultats trouvés
        QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
        // Afficher un message d'information avec le nombre de résultats trouvés
        QMessageBox::information(this, "Recherche", message);
        // Définir le modèle de résultats dans la table
        ui->tableView_2->setModel(model);
        // Trier les résultats par ordre croissant de l'id
        ui->tableView_2->sortByColumn(0, Qt::AscendingOrder);
    }
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1450,"Liste Des Vehicule");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 10));
    painter.drawText(300,3300,"ID");
    painter.drawText(1500,3300,"Kilométrage");
    painter.drawText(3000,3300,"Nom");
    painter.drawText(4800,3300,"Prenom");
    painter.drawText(6600,3300,"Marque");
    painter.drawText(8400,3300,"Modele");
    painter.drawText(10000,3300,"NumSerie");

    painter.drawRect(100,3000,9400,10700);

    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT * FROM vehicule");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(3000,i,query.value(2).toString());
        painter.drawText(4800,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8400,i,query.value(5).toString());
        painter.drawText(10000,i,query.value(6).toString());

        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }
}

void MainWindow::on_triID_3_clicked()
{
    ui->tableView_2->setModel(v.triID());
}

void MainWindow::on_nom_az_clicked()
{
    ui->tableView_2->setModel(v.triNOM());
}

void MainWindow::on_nom_desc_clicked()
{
    ui->tableView_2->setModel(v.triNOMdesc());
}

void MainWindow::on_ID_desc_2_clicked()
{
    ui->tableView_2->setModel(v.triIDdesc());
}

void MainWindow::on_trimodele_clicked()
{
    ui->tableView_2->setModel(v.trimodele());
}

void MainWindow::on_tritypedesc_2_clicked()
{
    ui->tableView_2->setModel(v.trimodeledesc());
}

void MainWindow::on_qrcodegen_2_clicked()
{
    int rowIndex = ui->tableView_2->currentIndex().row();
    QVariant idValue = ui->tableView_2->model()->data(ui->tableView_2->model()->index(rowIndex, 0));
    int id = idValue.toInt();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM vehicule WHERE id=:id");
    qry.bindValue(":id", id);
    qry.exec();

    QString qrText = "";
    while (qry.next()) {
        int NumSerie = qry.value(1).toInt();
        QString nom = qry.value(2).toString();
        QString prenom = qry.value(3).toString();
        QString marque = qry.value(4).toString();
        QString modele = qry.value(5).toString();
        int kilometrage = qry.value(6).toInt();

        // Create QR code text
        qrText = "NumSerie:" + QString::number(NumSerie) +
                 ",Nom:" + nom +
                 ",Prenom:" + prenom +
                 ",Marque:" + marque +
                 ",Modele:" + modele +
                 ",Kilometrage:" + QString::number(kilometrage);
    }

    QrCode qr = QrCode::encodeText(qrText.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage image(qr.getSize(), qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if (color == 0)
                image.setPixel(x, y, qRgb(254, 254, 254));
            else
                image.setPixel(x, y, qRgb(0, 0, 0));
        }
    }
    image = image.scaled(200, 200);
    ui->qrcode->setPixmap(QPixmap::fromImage(image));
}



void MainWindow::on_pushButton_3_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("SELECT type FROM vehicule ");
                                    float e=model->rowCount();
                                    model->setQuery("SELECT kilometrage FROM vehicule ");
                                    float ee=model->rowCount();
                                    float total=e+ee;
                                    QString a=QString("NumSerie"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("kilometrage"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
                            if (e!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( ee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des NumSerie et kilometrage : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}

void MainWindow::addPagination()
{


int currentPage = ui->tableView_2->currentIndex().row() / m_pageSize;
int rowCount = ui->tableView_2->model()->rowCount();

int startRow = currentPage * m_pageSize;
int endRow = qMin(startRow + m_pageSize, rowCount) - 1;

// Show only the rows for the current page
// QAbstractItemModel *model = ui->tabmedi_3->model();
for (int row = 0; row < rowCount; row++) {
if (row >= startRow && row <= endRow) {
ui->tableView_2->setRowHidden(row, false);
} else {
ui->tableView_2->setRowHidden(row, true);
}
}


/*
// Disable "Previous Month" and "Next Month" buttons if necessary
ui->moisprec->setEnabled(currentPage > 0);
ui->moisuivant->setEnabled(currentPage < totalPages - 1);
*/



}



void MainWindow::on_moisuivant_clicked()
{
    QModelIndex currentIndex = ui->tableView_2->currentIndex();
    int nextIndexRow = currentIndex.row() + m_pageSize;
    int rowCount = ui->tableView_2->model()->rowCount();
    if (nextIndexRow >= rowCount) {
    nextIndexRow = rowCount - 1;
    }

    m_currentPage = nextIndexRow / m_pageSize;
    addPagination();

    QModelIndex nextIndex = ui->tableView_2->model()->index(nextIndexRow, currentIndex.column());
    ui->tableView_2->setCurrentIndex(nextIndex);
}

void MainWindow::on_moisprec_clicked()
{
    m_currentPage--;
    if (m_currentPage < 0) {
    m_currentPage = 0;
    }
    addPagination();

    // Aller à la page précédente
    int prevPageStartRow = m_currentPage * m_pageSize;
    int rowCount = ui->tableView_2->model()->rowCount();
    if (prevPageStartRow < rowCount) {
    QModelIndex prevIndex = ui->tableView_2->model()->index(prevPageStartRow, 0);
    ui->tableView_2->setCurrentIndex(prevIndex);
    }
}

void MainWindow::on_Empl_push_reture_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


/*
////////////////////////////////////////////////////////////EQUIPEMENT////////////////////////////////////////////////////////////////////////
*/


void MainWindow::on_pb_ajouter_3_clicked()
{
    // Vérification que tous les champs sont remplis
    if(ui->leid_3->text().isEmpty() || ui->dateaa->text().isEmpty() || ui->lenomE->text().isEmpty() || ui->lestatut->text().isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Attention"), QObject::tr("Veuillez remplir tous les champs"));
        return;
    }

    //Récupération des informations saisies dans les 4 champs
       int id=ui->leid_3->text().toInt();
       int dateA=ui->dateaa->text().toInt();
       QString nomE=ui->lenomE->text();
       QString statut=ui->lestatut->text();

       //instancier un objet de la classe equipements
       //en utilisant les informations saisies dans l'interface
       Equipement Q(id,dateA,nomE,statut);

    //insérer l'objet equipement instancié dans la table equipement
    //et récupérer la valeur de retour de query.exec()
    bool test=Q.ajouter();

    //si la requete executée => QMessageBox::information
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres l'ajout
       ui->tabequipement->setModel(Q.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_supprimer_3_clicked()
{
    Equipement Q1;
    Q1.setid(ui->id_supp_5->text().toInt());

    bool test=Q1.supprimer(Q1.getid());

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Suppression effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres la suppression
       ui->tabequipement->setModel(Q1.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Suppression non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_modifier_3_clicked()
{
    //Récupération des informations saisies
    int id=ui->leid_3->text().toInt();
    int dateA=ui->dateaa->text().toInt();
    QString nomE=ui->lenomE->text();
    QString statut=ui->lestatut->text();

    Equipement Q(id,dateA,nomE,statut);

    bool test=Q.modifier(id);
    if(test)
    {
        ui->tabequipement->setModel(Q.afficher());
    }

    // Vérifier que l'identifiant saisi est valide
    if (id <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return;
    }

    // Vérification que tous les champs sont remplis
    if(ui->leid_3->text().isEmpty() || ui->dateaa->text().isEmpty() || ui->lenomE->text().isEmpty() || ui->lestatut->text().isEmpty())
    {
        QMessageBox::warning(nullptr, QObject::tr("Attention"), QObject::tr("Veuillez remplir tous les champs"));
        return;
    }

    // Vérifier que l'identifiant existe dans la table
        QSqlQuery query;
        query.prepare("SELECT * FROM Equipement WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec())
        {
                QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
                return;
        }
        if (!query.next())
        {
                QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
                return;
        }

        // Demander à l'utilisateur de confirmer la modification
            QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
                "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
                QMessageBox::Yes|QMessageBox::No);

            if (confirmUpdate == QMessageBox::No)
            {
                return; // L'utilisateur a annulé la modification, sortir de la fonction
            }

            // Exécuter la requête SQL pour mettre à jour l'enregistrement
                query.prepare("UPDATE Equipement SET id=:id, dateA=:dateA, nomE=:nomE, statut=:statut,  WHERE id=:id");
                query.bindValue(":id", id);
                query.bindValue(":dateA", dateA);
                query.bindValue(":nomE", nomE);
                query.bindValue(":statut", statut);

                if (query.exec())
                    {
                        QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Modification effectuée\n"
                                                 "Click Cancel to exit"), QMessageBox::Cancel);

                        //Actualiser le tableau après la modification
                        ui->tabequipement->setModel(Q.afficher());
                    }
                    else
                    {
                        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("Modification non effectuée\n"
                                                 "Click Cancel to exit"), QMessageBox::Cancel);
                    }
}

void MainWindow::on_pushButton_rechercher_2_clicked()
{
    // Récupérer la valeur de recherche et supprimer les espaces inutiles
    QString valeur = ui->lerechercher_2->text().trimmed();

    // Vérifier si la valeur de recherche est vide
    if (valeur.isEmpty())
    {
        // Afficher un message d'erreur
        QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
        // Quitter la fonction sans exécuter la recherche
        return;
    }

    // Appeler la fonction de recherche dans la classe Piste et récupérer le modèle de résultats
       QSqlQueryModel *model = Q.rechercher(valeur);

    // Vérifier si aucun résultat n'a été trouvé
    if (model->rowCount() == 0)
    {
        // Afficher un message d'information
        QMessageBox::information(this, "Recherche", "AQucun résultat trouvé.");
    }
    else
    {
        // Créer un message avec le nombre de résultats trouvés
        QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
        // Afficher un message d'information avec le nombre de résultats trouvés
        QMessageBox::information(this, "Recherche", message);
        // Définir le modèle de résultats dans la table
        ui->tabequipement->setModel(model);
        // Trier les résultats par ordre croissant de l'id
        ui->tabequipement->sortByColumn(0, Qt::AscendingOrder);
    }
}

void MainWindow::on_pushButton_PDF_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;

    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);

    int i = 4000;

    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1450,"Liste Des Vehicule");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 10));
    painter.drawText(300,3300,"ID");
    painter.drawText(1500,3300,"Date A");
    painter.drawText(3000,3300,"Nom E");
    painter.drawText(4800,3300,"Statut");
    painter.drawText(6600,3300,"");
    painter.drawText(8400,3300,"");
    painter.drawText(10000,3300,"");

    painter.drawRect(100,3000,9400,10700);

    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT * FROM equipement");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1500,i,query.value("dateA").toString());
        painter.drawText(3000,i,query.value("nomE").toString());
        painter.drawText(4800,i,query.value("statut").toString());

        i = i +500;
    }

    int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?", QMessageBox::Yes|QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
        painter.end();
    }
}

void MainWindow::on_triID_4_clicked()
{
    ui->tabequipement->setModel(Q.triID());
}

void MainWindow::on_nom_az_2_clicked()
{
    ui->tabequipement->setModel(Q.triNOM());
}

void MainWindow::on_nom_az_3_clicked()
{
    ui->tabequipement->setModel(Q.triNOMdesc());
}

void MainWindow::on_ID_desc_3_clicked()
{
    ui->tabequipement->setModel(Q.triIDdesc());
}

void MainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tabequipement);

    //colums to export
    obj.addField(0, "id", "char(20)");
    obj.addField(1, "nomE", "char(20)");
    obj.addField(2, "dateA", "char(20)");
    obj.addField(3, "statut", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)//fichier enregistré dans dossier debug(build)
                                 );
    }
}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("chedlybahles12@gmail.com","211JMT7058", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
   QStringList attachments;
     foreach(QString filename, files)
     {
         attachments << filename;
     }
    if( !files.isEmpty() )
        smtp->sendMail("chedlybahles12@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(),attachments);
    else
        smtp->sendMail("chedlybahles12@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(),attachments);

    ui->rcpt->setText("");
    ui->subject->setText("");
    ui->msg->setPlainText("");
    files.clear();
}

void MainWindow::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file,files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );


    ui->file->setText( fileListString );
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("SELECT type FROM equipement ");
                                    float e=model->rowCount();
                                    model->setQuery("SELECT dateA FROM equipement ");
                                    float ee=model->rowCount();
                                    float total=e+ee;
                                    QString a=QString("NumSerie"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("id"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
                            if (e!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( ee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des id et dateA : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}

void MainWindow::on_Empl_push_reture_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




/*
////////////////////////////////////////////////////////////RESERVATION////////////////////////////////////////////////////////////////////////
*/

void MainWindow::on_Reserv_retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}









































/*
////////////////////////////////////////////////////////////VISITES////////////////////////////////////////////////////////////////////////
*/

void MainWindow::on_Visites_retour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pb_ajouter_4_clicked()
{
    QMessageBox msgbox;

        //Récupération des informations saisies dans les 5 champs
        int id=ui->leid_2->text().toInt();
       QString nom=ui->res_nom->text();
        QString prenom=ui->res_prenom->text();
        QString type_immatriculation=ui->type_immatriculation->text();
       int numImmatriculation=ui->le_numImmatriculation->text().toInt();
       QDateTime date_res=ui->date_res->dateTime();
        QRegularExpression regex("^\\+216[0-9]{8}$");
        QRegExp regex1("^[A-Za-z]+$");
        //instancier un objet de la classe reservation
        //en utilisant les informations saisies dans l'interface
        Reservation R(id, nom, prenom, type_immatriculation, numImmatriculation, date_res);

        //insérer l'objet reservation instancié dans la table reservation
        //et récupérer la valeur de retour de query.exec()
        bool test=R.ajouter();

        //si la requete executée => QMessageBox::information
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Ajout effectué\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
            R.ajouter_historique("ajout",numImmatriculation,id);
            ui->tableView_his->setModel(R.afficher_historique0());
            //Actualiser le tableau apres l'ajout
            ui->tab_reservation->setModel(R.afficher());

        }
        //si la requete non exécuté => QMessageBox::critical
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("Ajout non effectué\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
        }
}

void MainWindow::on_pb_modifier_4_clicked()
{
    QMessageBox msgbox;
    //Récupération des informations saisies dans les 5 champs
        int id=ui->leid_2->text().toInt();
        QString nom=ui->res_nom->text();
        QString prenom=ui->res_prenom->text();
      QString type_immatriculation=ui->type_immatriculation->text();
        int numImmatriculation=ui->le_numImmatriculation->text().toInt();
        QDateTime date_res=ui->date_res->dateTime();


        // Vérifier que l'identifiant saisi est valide
        if (id <= 0)
        {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
            return;
        }
        // Vérifier que les champs obligatoires sont remplis
            if (nom .isEmpty()|| prenom .isEmpty() || numImmatriculation <= 0 ||type_immatriculation.isEmpty() )
            {
                QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
                return;
            }

        // Vérifier que l'identifiant existe dans la table
        QSqlQuery query;
        query.prepare("SELECT * FROM reservation WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
            return;
        }
        if (!query.next())
        {
            QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
            return;
        }

        // Demander à l'utilisateur de confirmer la modification
        QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmUpdate == QMessageBox::No) {
            return; // L'utilisateur a annulé la modification, sortir de la fonction
        }

        // Exécuter la requête SQL pour mettre à jour l'enregistrement
        query.prepare("UPDATE reservation SET nom = :nom, prenom = :prenom, type_immatriculation = :type_immatriculation, numImmatriculation = :numImmatriculation WHERE id = :id");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":type_immatriculation", type_immatriculation);
        query.bindValue(":numImmatriculation", numImmatriculation);
        query.bindValue(":id", id);

        if (query.exec())
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Modification effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
            R.ajouter_historique("modification",numImmatriculation,id);
                    ui->tableView_his->setModel(R.afficher_historique0());
            //Actualiser le tableau après la modification
            ui->tab_reservation->setModel(R.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("Modification non effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
            R.ajouter_historique("modification",numImmatriculation,id);
                    ui->tableView_his->setModel(R.afficher_historique0());
        }
}



void MainWindow::on_pb_supprimer_4_clicked()
{
    QMessageBox msgbox;
    // Récupérer l'identifiant de l'enregistrement à supprimer
    int id = ui->id_supp_6->text().toInt();

    if (id <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
        return; // Sortir de la fonction si l'identifiant est invalide
    }

    // Vérifier si l'identifiant existe dans la table
    QSqlQuery query;

    query.prepare("SELECT * FROM reservation WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
        return; // Sortir de la fonction en cas d'erreur de requête
    }
    if (!query.next())
    {
        QMessageBox::warning(this, "Attention", "L'identifiant à supprimer n'existe pas dans la table.");
        return; // Sortir de la fonction si l'identifiant n'existe pas dans la table
    }

    // Demander à l'utilisateur de confirmer la suppression
        QMessageBox::StandardButton confirmDelete = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir supprimer cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmDelete == QMessageBox::No) {
            return; // L'utilisateur a annulé la suppression, sortir de la fonction
        }
   Reservation R1;
    R1.setid(ui->id_supp_6->text().toInt());

    bool test=R1.supprimer(R1.getid());

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Suppression effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
        R.ajouter_historique("suppression",ui->le_numImmatriculation->text().toInt(),ui->leid_2->text().toInt());
        ui->tableView_his->setModel(R.afficher_historique0());

        //Actualiser le tableau apres la suppression
        ui->tab_reservation->setModel(R.afficher());
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Suppression non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }
}

void MainWindow::on_pb_rechercher_2_clicked()
{
    // Récupérer la valeur de recherche et supprimer les espaces inutiles
    QString valeur = ui->le_recherche->text().trimmed();

    // Vérifier si la valeur de recherche est vide
    if (valeur.isEmpty())
    {
        // Afficher un message d'erreur
        QMessageBox::warning(this, "Recherche", "Veuillez saisir une valeur de recherche.");
        // Quitter la fonction sans exécuter la recherche
        return;
    }

    // Appeler la fonction de recherche dans la classe Reservation et récupérer le modèle de résultats
    QSqlQueryModel *model = R.rechercher(valeur);

    // Vérifier si aucun résultat n'a été trouvé
    if (model->rowCount() == 0)
    {
        // Afficher un message d'information
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé.");
    }
    else
    {
        // Créer un message avec le nombre de résultats trouvés
        QString message = QString("%1 résultat(s) trouvé(s).").arg(model->rowCount());
        // Afficher un message d'information avec le nombre de résultats trouvés
        QMessageBox::information(this, "Recherche", message);
        // Définir le modèle de résultats dans la table
        ui->tab_reservation->setModel(model);
        // Trier les résultats par ordre croissant de l'id
        ui->tab_reservation->sortByColumn(0, Qt::AscendingOrder);
    }
}

void MainWindow::on_triID_5_clicked()
{
    ui->tab_reservation->setModel(R.triID());
}

void MainWindow::on_ID_desc_4_clicked()
{
    ui->tab_reservation->setModel(R.triIDdesc());
}


void MainWindow::on_Empl_push_ExportPDF_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/msi.png"));
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1450,"Liste Des Réservations");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 10));
    painter.drawText(300,3300,"ID");
    painter.drawText(1500,3300,"Nom");
    painter.drawText(3000,3300,"Prénom");
    painter.drawText(4800,3300,"Type_imm");
    painter.drawText(6600,3300,"Num_imm");
    painter.drawText(8400,3300,"Date_res");


    painter.drawRect(100,3000,9400,10700);

    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT * FROM vehicule");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(3000,i,query.value(2).toString());
        painter.drawText(4800,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8400,i,query.value(5).toString());


        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }






















    /*
    // Définition de la chaîne HTML pour l'impression

        QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tab_reservation->model()->rowCount();
        const int columnCount =ui->tab_reservation->model()->columnCount();

        out <<  "<html>\n"

                "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("application")

                 <<  "</head>\n"

                 "<body bgcolor=#d8f0eb link=#cfe3dc>\n"

                                "<h1>Liste des Reservation</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers

                        out << "<thead><tr bgcolor=#f0f0f0>";

                        for (int column = 0; column < columnCount; column++)

                            if (!ui->tab_reservation->isColumnHidden(column))

                                out << QString("<th>%1</th>").arg(ui->tab_reservation->model()->headerData(column, Qt::Horizontal).toString());

                        out << "</tr></thead>\n";

                        // data table

                           for (int row = 0; row < rowCount; row++) {

                               out << "<tr>";

                               for (int column = 0; column < columnCount; column++) {

                                   if (!ui->tab_reservation->isColumnHidden(column)) {

                                       QString data = ui->tab_reservation->model()->data(ui->tab_reservation->model()->index(row, column)).toString().simplified();

                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

            QTextDocument *document = new QTextDocument();

            document->setHtml(strStream);

            //QTextDocument document;
            //document.setHtml(html);

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("mypdffile.pdf");
            document->print(&printer);*/
}

void MainWindow::on_Empl_push_Statistiques_2_clicked()
{
    //Créer une instance de la classe QSqlQueryModel pour récupérer les données de la base de données.
    QSqlQueryModel * model= new QSqlQueryModel();

    //Exécuter une requête SQL pour récupérer le type de chaque piste de la table "piste".
    model->setQuery("SELECT type_immatriculation FROM Reservation  ");
    //Obtenir le nombre de résultats retournés par la requête précédente et le stocker dans la variable e.
    float e=model->rowCount();

    //Exécuter une requête SQL pour récupérer le numéro de chaque piste de la table "piste".
    model->setQuery("SELECT numImmatriculation FROM Reservation ");
    float ee=model->rowCount();

    //Calculer le nombre total de pistes en additionnant les variables e et ee.
    float total=e+ee;

    QString a=QString("type_immatriculation"+QString::number((e*100)/total,'f',2)+"%" );
    QString b=QString("numImmatriculation"+QString::number((ee*100)/total,'f',2)+"%" );

    // Créer une instance de la classe QPieSeries pour stocker les données du graphique à secteurs.
    QPieSeries *series = new QPieSeries();

    series->append(a,e);
    series->append(b,ee);

    if (e!=0)
    {
        // Créer une instance de la classe QPieSeries pour stocker les données du graphique à secteurs.
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if ( ee!=0)
    {
         // Add label, explode and define brush for 2nd slice
         QPieSlice *slice1 = series->slices().at(1);
         //slice1->setExploded();
         slice1->setLabelVisible();
     }

     // Create the chart widget
     QChart *chart = new QChart();

     // Add data to chart with title and hide legend
     chart->addSeries(series);

     chart->setTitle("Pourcentage des type_immatriculation et type_immatriculation : nombre total : "+ QString::number(total));
     chart->legend()->hide();

     // Used to display the chart
     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     chartView->resize(1000,500);
     chartView->show();
}


/*
 * ////////////////HISTO
 */
void MainWindow::on_aff_clicked()
{
     Reservation R;
     QString type=ui->typehistorique->currentText();
     ui->tableView_his->setModel(R.afficher_historique(type));
}

void MainWindow::on_supphistorique_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE from history");
    query.exec();
}

void MainWindow::on_supphistorique_2_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet reservation ?", QMessageBox ::Yes | QMessageBox::No);

    Reservation R;
    R.setid(ui->nomsupp->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        bool test=R.supprimer(R.getid());
        if(test)
        {
            msgbox.setText("suppression avec succes");
        }
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }

    msgbox.exec();
}

void MainWindow::on_pdfhistorique_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_his->model()->rowCount();
    const int columnCount = ui->tableView_his->model()->columnCount();

    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        "<style>\n"
        "table {"
        "   border-collapse: collapse;"
           "  border-style: dotted;"
        "   width: 50%;"
        "   margin-bottom: 20px;"
        "}"
        "table, th, td {"
        "   border: 10px solid black;"
        "   padding: 5px;"
        "}"
        "thead {"
        "   background-color: #f0f0f0;"
        "}"
        "</style>\n"
        << QString("<title>%1</title>\n").arg("strTitle")
        << "</head>\n"
        "<body>\n"
        "<center><h1>Historique</h1></center>\n"
        "<table>\n";

    // headers
    out << "<thead><tr> <th>Numero</th>";

    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_his->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_his->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_his->isColumnHidden(column))
            {
                QString data = ui->tableView_his->model()->data(ui->tableView_his->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</table>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
    //QString imagePath = "C:\Users\yosse_yqbk87k\Desktop\";
    //QImage logo(imagePath);
    //doc.addResource(QTextDocument::ImageResource, QUrl("logo"), logo); // Ajouter l'image en tant que ressource
    doc.setHtml(strStream);

    QPainter painter;
    painter.begin(&printer);

    // Dessiner l'image dans le coin supérieur gauche
    //painter.drawImage(QRectF(10, 10, 100, 100), logo);

    doc.drawContents(&painter);
    painter.end();
}

void MainWindow::on_tableView_his_activated(const QModelIndex &index)
{
    QString val=ui->tableView_his->model()->data(index).toString();

    QSqlQuery qry;

    qry.prepare("SELECT *from history where id='"+val+"' ");
    if (qry.exec())
    {
        while(qry.next())
        {
            ui->nomsupp->setText(qry.value(2).toString());
        }
    }
    else
        QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );
}






















/*
////////////////////////ARDUINO BARRIERE/////////////////////////////////////////////////////
*/

void MainWindow::update_label_1()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->label_3->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->label_3->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void MainWindow::on_pushButton_11_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino

}

void MainWindow::on_pushButton_12_clicked()
{
     A.write_to_arduino("0");  //envoyer 0 à arduino
}

/*
////////////////////////ARDUINO PORTE/////////////////////////////////////////////////////
*/
void MainWindow::update_label_2()
{
    data="";

    data=B.read_from_arduino();

    qDebug()<<data;
    if(data!="")
    {
        if(B.chercherid(data)!=-1)
        {
            QString nom=B.chercher(data);
            qDebug() << nom ;
            QByteArray x=nom.toUtf8();
            qDebug() << x ;
            B.write_to_arduino(x);
            qDebug()<<"valdie";

             }
        else
        {
            B.write_to_arduino("0"); qDebug()<<"invaldie"; }
    }
}


/*
 /////////////////////////////////////////////////////////////////////////////////////
 */



void MainWindow::on_pb_ajouter_5_clicked()
{
    //Récupération des informations saisies dans les 5 champs
    QMessageBox msgbox;
       notification n;
       int id=ui->leid_4->text().toInt();
       int datevisite=ui->le_datevisite->text().toInt();
       int kilometrage=ui->le_kilometrage->text().toInt();
       int prixvisite=ui->le_prixvisite->text().toInt();
       QString resultat=ui->le_resultat->currentText();


       //instancier l'objet de la classe vehicule
       Visite s(id,datevisite,kilometrage,prixvisite,resultat);

    //insérer l'objet piste instancié dans la table piste
    //et récupérer la valeur de retour de query.exec()
    bool test=s.ajouter();

    //si la requete executée => QMessageBox::information
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);

        //Actualiser le tableau apres l'ajout
        ui->tab_visite->setModel(s.afficher());
         n.notification_ajout();
    }
    //si la requete non exécuté => QMessageBox::critical
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click Cancel to exit"), QMessageBox::Cancel);
    }


}

void MainWindow::on_pb_modifier_5_clicked()
{
    int id=ui->leid_4->text().toInt();
    int datevisite=ui->le_datevisite->text().toInt();
    int kilometrage=ui->le_kilometrage->text().toInt();
    int prixvisite=ui->le_prixvisite->text().toInt();
    QString resultat=ui->le_resultat->currentText();



Visite s(id,datevisite,kilometrage,prixvisite,resultat);
bool test=s.modifier(id);
if(test){
ui->tab_visite->setModel(s.afficher());}
// Vérifier que l'identifiant saisi est valide
        if (id <= 0)
        {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer une valeur numérique valide pour l'identifiant.");
            return;
        }
        // Vérifier que les champs obligatoires sont remplis
            if (datevisite <=0|| kilometrage <=0||prixvisite <=0|| resultat.isEmpty()  )
            {
                QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
                return;
            }

        // Vérifier que l'identifiant existe dans la table
        QSqlQuery query;
        query.prepare("SELECT * FROM visite WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec())
        {
            QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la vérification de l'identifiant.");
            return;
        }
        if (!query.next())
        {
            QMessageBox::warning(this, "Attention", "L'identifiant à modifier n'existe pas dans la table.");
            return;
        }

        // Demander à l'utilisateur de confirmer la modification
        QMessageBox::StandardButton confirmUpdate = QMessageBox::question(this, "Confirmation",
            "Êtes-vous sûr de vouloir modifier cet enregistrement ?",
            QMessageBox::Yes|QMessageBox::No);

        if (confirmUpdate == QMessageBox::No) {
            return; // L'utilisateur a annulé la modification, sortir de la fonction
        }

        // Exécuter la requête SQL pour mettre à jour l'enregistrement

        query.prepare("UPDATE visite SET datevisite = :datevisite, kilometrage= :kilometrage, prixvisite = :prixvisite ,resultat = :resultat WHERE id = :id");
        query.bindValue(":id", id);
        query.bindValue(":datevisite", datevisite);
        query.bindValue(":kilometrage", kilometrage);
        query.bindValue(":prixvisite", prixvisite);
        query.bindValue(":resultat", resultat);



        if (query.exec())
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("Modification effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);

            //Actualiser le tableau après la modification
            ui->tab_visite->setModel(s.afficher());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                         QObject::tr("Modification non effectuée\n"
                                     "Click Cancel to exit"), QMessageBox::Cancel);
        }
}

void MainWindow::on_pb_supprimer_5_clicked()
{
    Visite s;
    s.setid(ui->itemId->text().toInt());
    bool test=s.supprimer(s.getid());
    if(test)
    {
        QMessageBox::information(this, "Succès", "Suppression avec succès.");
        ui->tab_visite->setModel(s.afficher());


    }
    else
    {
       QMessageBox::warning(this, "Erreur", "La visite n'existe pas.");
    }
}

void MainWindow::on_pb_rechercher_4_clicked()
{
    QString rech =ui->lerechercher->text();
        ui->tab_visite->setModel(v.rechercher(rech));
}

void MainWindow::on_pushButton_PDF_3_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Mahmoud Omar/Desktop"));
    painter.setPen(Qt::red);
    painter.setFont(QFont("Time New Roman", 25));
    painter.drawText(3000,1450,"Liste Des Visites");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);
    painter.setFont(QFont("Time New Roman", 10));
    painter.drawText(300,3300,"ID");
    painter.drawText(1500,3300,"Datevisite");
    painter.drawText(3000,3300,"Kilometrage");
    painter.drawText(4800,3300,"Prixvisite");
    painter.drawText(6600,3300,"Resultat");


    painter.drawRect(100,3000,9400,10700);

    QTextDocument previewDoc;
    QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");

    QTextCursor cursor(&previewDoc);

    QSqlQuery query;
    query.prepare("SELECT * FROM visite");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(1500,i,query.value(1).toString());
        painter.drawText(3000,i,query.value(2).toString());
        painter.drawText(4800,i,query.value(3).toString());
        painter.drawText(6600,i,query.value(4).toString());
        painter.drawText(8400,i,query.value(5).toString());
        painter.drawText(10000,i,query.value(6).toString());

        i = i +500;
    }
    int reponse = QMessageBox::question(this, "Générer PDF", " PDF Enregistré ! Voulez Vous Affichez Le PDF ?",
                                            QMessageBox::Yes|QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));
        painter.end();
    }
    else
    {
         painter.end();
    }
}

void MainWindow::on_statsmed_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from visite where resultat='Accepter' ");
     int number1=model->rowCount();
     model->setQuery("select * from visite where resultat ='Refuser' ");
     int number2=model->rowCount();

     int total=number1+number2;
     QString a = QString("Accepter"+QString::number((number1*100)/total,'f',2)+"%" );
     QString b = QString("Refuser"+QString::number((number2*100)/total,'f',2)+"%" );



     QPieSeries *series = new QPieSeries();
     series->append(a,number1);
     series->append(b,number2);

     if (number1!= 0)
     {
         QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());
     }
     if (number2!=0)
     {
              // Add label, explode and define brush for 2nd slice
              QPieSlice *slice1 = series->slices().at(1);
              //slice1->setExploded();
              slice1->setLabelVisible();
     }


             // Create the chart widget
             QChart *chart = new QChart();
             // Add data to chart with title and hide legend
             chart->addSeries(series);
             chart->setTitle("Pourcentage Par resultat "+ QString::number(total));
             chart->legend()->hide();
             // Used to display the chart
             QChartView *chartView = new QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             chartView->resize(1000,500);
             chartView->show();
}

void MainWindow::on_triID_6_clicked()
{
    ui->tab_visite->setModel(v.triID());
}

void MainWindow::on_ID_desc_5_clicked()
{
    ui->tab_visite->setModel(v.triIDdesc());
}

void MainWindow::on_pushButton_encrypt_clicked()
{
    QString plainText = ui->plainTextEdit_plain->toPlainText();
    QString encryptedText = "to be implemented";

    if(ui->comboBox->currentIndex() == 0)
    {
        int key = ui->lineEdit_CC_key->text().toInt();
        encryptedText = ewCaesarCipher(plainText, key);
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        QString secret = ui->lineEdit_PF_Secret->text();
        encryptedText = ewPlayfair(plainText, secret);
    }
    else if(ui->comboBox->currentIndex() == 2)
    {
        QString key = ui->lineEdit_DES_key_3->text();
        encryptedText = ewDES(plainText, key.toStdString());
    }
    else if(ui->comboBox->currentIndex() == 3)
    {
      double p = ui->RSA_lineEdit_p_2->text().toDouble();
      double q = ui->RSA_lineEdit_q_2->text().toDouble();
       double dbl = ewRSA(plainText.toDouble(), p, q);

        std::ostringstream strs;
        strs << dbl;
        encryptedText = QString::fromStdString(strs.str());

        std::pair<double, double> pair = RSAKeys(p, q);
        std::ostringstream strPrK;
        strPrK << pair.first;
        ui->RSA_lineEdit_prkey_2->setText(QString::fromStdString(strPrK.str()));
        std::ostringstream strPuK;
        strPuK << pair.second;
      ui->RSA_lineEdit_pukey_2->setText(QString::fromStdString(strPuK.str()));
    }
    else if(ui->comboBox->currentIndex() == 4)
    {
        QString key = ui->lineEdit_rc4_key_3->text();
        encryptedText = ewRC4(plainText, key);
    }
    else if(ui->comboBox->currentIndex() == 5)
    {
        QString key = ui->lineEdit_DES_key_3->text();
        encryptedText = ewIDES(plainText, key.toStdString());
    }
    ui->plainTextEdit_encrypted->document()->setPlainText(encryptedText);
}
void MainWindow::on_actionReset_Fields_triggered()
{
    ui->plainTextEdit_plain->clear();
    ui->plainTextEdit_encrypted->clear();
    ui->lineEdit_CC_key->clear();
}

void MainWindow::on_actionClear_Plain_Text_triggered()
{
    ui->plainTextEdit_plain->clear();
}

void MainWindow::on_actionClear_Encrypted_Text_triggered()
{
    ui->plainTextEdit_encrypted->clear();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Caesar Cipher")
    {
        ui->stackedWidget_3->setCurrentIndex(0);
    }
    else if(arg1 == "Playfair")
    {
        ui->stackedWidget_3->setCurrentIndex(1);
    }
    else if(arg1 == "DES")
    {
        ui->stackedWidget_3->setCurrentIndex(2);
    }
    else if(arg1 == "RSA")
    {
        ui->stackedWidget_3->setCurrentIndex(3);
    }
    else if(arg1 == "RC4")
    {
        ui->stackedWidget_3->setCurrentIndex(4);
    }
    else if(arg1 == "DES with Text")
    {
        ui->stackedWidget_3->setCurrentIndex(2);
    }
}





// Caesar Cipher Methods

QString MainWindow::ewCaesarCipher(QString plainText, int key)
{
    std::string result = "";
    std::string plainStdText = plainText.toStdString();

    for (int i=0;i<plainText.length();i++)
    {
        if(plainStdText[i] == ' ')
        {
            result += ' ';
        }
        else if(std::isalpha(plainStdText[i]))
        {
            if (std::isupper(plainStdText[i]))
                result += char(int(plainStdText[i]+key-65)%26 +65);
            else
                result += char(int(plainStdText[i]+key-97)%26 +97);
        }
    }

    return QString::fromStdString(result);
}

QString MainWindow::dwCaesarCipher(QString encryptedText, int key)
{
    return ewCaesarCipher(encryptedText, 26-key);
}





// playfair Methods

QString MainWindow::ewPlayfair(QString plainText, QString secret)
{
    std::string plainStdText = plainText.toStdString();
    std::string secretStdText = secret.toStdString();

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);
    normalizePFString(plainStdText);

    std::string encryptedText = encryptPFString(plainStdText);

    return QString::fromStdString(encryptedText);
}

QString MainWindow::dwPlayfair(QString encryptedText, QString secret)
{
    std::string encryptedStdText = encryptedText.toStdString();
    std::string secretStdText = secret.toStdString();

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);

    std::string plainText = decryptPFString(encryptedStdText);

    return QString::fromStdString(plainText);
}

bool MainWindow::inSameRow(Position p1, Position p2)
{
    if(p1.x == p2.x)
        return true;
    return false;
}

bool MainWindow::inSameColumn(Position p1, Position p2)
{
    if(p1.y == p2.y)
        return true;
    return false;
}

void MainWindow::normalizePFString(std::string &str)
{
    std::string pure_str= "";
    // remove any non-alphabetical characters
    // convert string to lower case
    for(int i=0;i<str.size();++i)
    {
        if(isalpha(str[i]))
        {
            if(std::isupper(str[i]))
                str[i] = std::tolower(str[i]);
            pure_str += str[i];
        }
    }

    // separate duplicate characters
    for(int i=0 ; i<pure_str.size()-1 ; i+=2)
    {
        if(pure_str[i] == pure_str[i+1])
            pure_str.insert(pure_str.begin()+i+1, 'x');
    }

    // make string even
    if(pure_str.size()%2 !=0)
        pure_str += 'x';

    str = pure_str;
}

std::string MainWindow::encryptPFString(std::string plainStdText)
{
    std::string result = "";

    for(int i=0;i<plainStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(plainStdText[i]);
        Position p2 = findPositionByChar(plainStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 4)
                p1.y = 0;
            else
                p1.y +=1;

            if(p2.y == 4)
                p2.y = 0;
            else
                p2.y +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 4)
                p1.x = 0;
            else
                p1.x +=1;

            if(p2.x == 4)
                p2.x = 0;
            else
                p2.x +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

std::string MainWindow::decryptPFString(std::string encryptedStdText)
{
    std::string result = "";

    for(int i=0;i<encryptedStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(encryptedStdText[i]);
        Position p2 = findPositionByChar(encryptedStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 0)
                p1.y = 4;
            else
                p1.y -=1;

            if(p2.y == 0)
                p2.y = 4;
            else
                p2.y -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 0)
                p1.x = 4;
            else
                p1.x -=1;

            if(p2.x == 0)
                p2.x = 4;
            else
                p2.x -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

void MainWindow::normalizePFSecret(std::string &secret)
{
    std::string result = "";
    secret += "abcdefghiklmnopqrstuvwxyz";
    for(int i=0;i<secret.size();++i)
    {
        if(result.find(secret[i]) == std::string::npos)
            result += secret[i];
    }
    secret = result;
}

void MainWindow::populatePFMatrix(std::string secret)
{
    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5 ; ++j)
        {
            pfMatrix[i][j] = secret[j+5*i];
        }
    }
}

Position MainWindow::findPositionByChar(char ch)
{
    Position p;

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            if(pfMatrix[i][j] == ch)
            {
                p.x = i;
                p.y = j;
            }
        }
    }

    return p;
}

char MainWindow::findCharByPosition(Position p)
{
    return pfMatrix[p.x][p.y];
}





// data 0000000100100011010001010110011110001001101010111100110111101111
// key  0001001100110100010101110111100110011011101111001101111111110001

// DES Methods

QString MainWindow::ewDES(QString plainText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);

    QString encryptedText = DESEncryption(plainText.toStdString(), keys);

    return encryptedText;
}

QString MainWindow::dwDES(QString encryptedText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);

    std::reverse(keys.begin(), keys.end());

    QString plainText = DESEncryption(encryptedText.toStdString(), keys);

    return plainText;
}

std::vector< std::string > MainWindow::keyPreparation(std::string key)
{
    // 0001001100110100010101110111100110011011101111001101111111110001

    std::string permutedKey = "";
    int PC1_permutations[56] = {
        57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
    };

    for(int i=0;i<56; ++i)
    {
        permutedKey += key[PC1_permutations[i]-1];
    }

//    std::cout << key << std::endl;
//    std::cout << permutedKey << std::endl;
//    std::cout << permutedKey.length() << std::endl;


    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    std::vector< std::pair<std::string, std::string> > keys;

    std::string C0 = permutedKey.substr(0,28);
    std::string D0 = permutedKey.substr(28,56);

//    std::cout << "C0 : " << C0 << std::endl;
//    std::cout << "D0 : " << D0 << std::endl;

    keys.push_back(std::make_pair(C0, D0));

    for(int i=1 ; i<17 ; ++i)
    {
        std::string C = keys[i-1].first;
        std::string D = keys[i-1].second;

        C = C.substr(shifts[i-1], C.length()) + C.substr(0, shifts[i-1]);
        D = D.substr(shifts[i-1], D.length()) + D.substr(0, shifts[i-1]);

        keys.push_back(std::make_pair(C, D));

//        std::cout << "C" << i << " : " << C << std::endl;
//        std::cout << "D" << i << " : " << D << std::endl;
    }


    int PC2_permutations[48] = {
        14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };

    std::vector<std::string> finalKeys;

    for(int i=0;i<16;++i)
    {
        std::string k = keys[i+1].first + keys[i+1].second;
        std::string fk = "";

        for(int j=0;j<48;++j)
        {
            fk += k[PC2_permutations[j]-1];
        }
        finalKeys.push_back(fk);
//        std::cout << fk << std::endl;
    }

    //std::cout << std::endl << ">[BEGIN] Keys generated Successfully" << std::endl << std:: endl;

    //for(int i=0; i<finalKeys.size(); ++i)
    //{
       // std::cout << "Key " << i+1 << ": " << finalKeys[i] << std::endl;
    //}

    //std::cout << std::endl << ">[END] Keys generated Successfully" << std::endl << std:: endl;


    return finalKeys;
}

QString MainWindow::DESEncryption(std::string dataBlock, std::vector< std::string > keys)
{
    // 0000000100100011010001010110011110001001101010111100110111101111

    std::string permutedBlock = "";

    int initPermutation[64] = {
        58,    50,   42,    34,    26,   18,    10,    2,
        60,    52,   44,    36,    28,   20,    12,    4,
        62,    54,   46,    38,    30,   22,    14,    6,
        64,    56,   48,    40,    32,   24,    16,    8,
        57,    49,   41,    33,    25,   17,     9,    1,
        59,    51,   43,    35,    27,   19,    11,    3,
        61,    53,   45,    37,    29,   21,    13,    5,
        63,    55,   47,    39,    31,   23,    15,    7
    };

    for(int i=0 ; i<64 ; ++i)
    {
        permutedBlock += dataBlock[initPermutation[i]-1];
    }

    std::string L0 = permutedBlock.substr(0, 32);
    std::string R0 = permutedBlock.substr(32, 64);


    //std::cout << "L0 : " << L0 << std::endl;
    //std::cout << "R0 : " << R0 << std::endl;

    std::vector< std::pair<std::string, std::string> > data;
    data.push_back(std::make_pair(L0, R0));

    for(int i=1;i<17;++i)
    {
        std::string L = data[i-1].second;

        std::string R = apply_xor(
            data[i-1].first,
            apply_func_F(apply_func_E(data[i-1].second), keys[i-1])
        );

        data.push_back(std::make_pair(L, R));

        //std::cout << "L" << i << " : " << L << std::endl;
        //std::cout << "R" << i << " : " << R << std::endl;
    }

    std::string encryptedDataReversedKey = "";
    encryptedDataReversedKey += data[data.size()-1].second;
    encryptedDataReversedKey += data[data.size()-1].first;

    std::string finalPermutedBlock = "";

    int finalPermutation[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
    };

    for(int i=0 ; i<64 ; ++i)
    {
        finalPermutedBlock += encryptedDataReversedKey[finalPermutation[i]-1];
    }

    return QString(finalPermutedBlock.c_str());
}

std::string MainWindow::apply_xor(std::string str1, std::string str2)
{
    //if(str1.length() != str2.length())
       // std::cout << "Error in XORed Strings, Length Not Equal" << std::endl;

    std::string result = "";
    for(int i=0;i<str1.length();++i)
    {
        if(str1[i] == str2[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

std::string MainWindow::apply_func_F(std::string str1, std::string str2)
{
    // result is 48 bit
    std::string result = apply_xor(str1, str2);

    int sboxes[8][4][16] =
    {
        {
            { 14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7 },
            {  0, 15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8 },
            {  4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0 },
            { 15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13 }
        },
        {
            { 15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10 },
            {  3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5 },
            {  0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15 },
            { 13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9 }
        },
        {
            { 10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8 },
            { 13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1 },
            { 13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7 },
            {  1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12 }
        },
        {
            {  7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15 },
            { 13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9 },
            { 10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4 },
            {  3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14 }
        },
        {
            {  2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9 },
            { 14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6 },
            {  4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14 },
            { 11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3 }
        },
        {
            { 12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11 },
            { 10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8 },
            {  9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6 },
            {  4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13 }
        },
        {
            {  4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1 },
            { 13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6 },
            {  1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2 },
            {  6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12 }
        },
        {
            { 13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7 },
            {  1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2 },
            {  7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8 },
            {  2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11 }
        }
    };

    std::string output = "";
    std::string outerBits = "";
    std::string innerBits = "";

    for(int i=0, s=0 ; i<48 ; i+=6, s++)
    {
        outerBits += result[i];
        outerBits += result[i+5];

        innerBits += result[i+1];
        innerBits += result[i+2];
        innerBits += result[i+3];
        innerBits += result[i+4];

        int row = std::stoi(outerBits, nullptr, 2);
        int column = std::stoi(innerBits, nullptr, 2);

        int valInSBox = sboxes[s][row][column];

        output += std::bitset<4>(valInSBox).to_string();

        outerBits = "";
        innerBits = "";
    }

    std::string permutedOutput = "";

    int permutations[32] = {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };

    for(int i=0; i<32; ++i)
    {
        permutedOutput += output[permutations[i]-1];
    }

    return permutedOutput;
}

std::string MainWindow::apply_func_E(std::string str)
{
    std::string result = "";

    int ePermutations[48] = {
         32,     1,    2,     3,     4,    5,
          4,     5,    6,     7,     8,    9,
          8,     9,   10,    11,    12,   13,
         12,    13,   14,    15,    16,   17,
         16,    17,   18,    19,    20,   21,
         20,    21,   22,    23,    24,   25,
         24,    25,   26,    27,    28,   29,
         28,    29,   30,    31,    32,    1
    };

    for(int i=0;i<48;++i)
    {
        result += str[ePermutations[i]-1];
    }

    return result;
}


// improved DES with text Methods
QString MainWindow::ewIDES(QString plainText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);
    std::vector< std::string > blocks = textToBinaryAscii(plainText.toStdString());

    QString encryptedText;

    for(int i=0; i<blocks.size(); ++i)
        encryptedText += DESEncryption(blocks[i], keys);

//    encryptedText = QString::fromStdString(binaryAsciiToText(encryptedText.toStdString()));

    return encryptedText;
}

QString MainWindow::dwIDES(QString encryptedText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);
    std::reverse(keys.begin(), keys.end());

    std::string stdPlainText = encryptedText.toStdString();
    std::string allPlainText = "";

    for(int i=0; i<encryptedText.size()/64; ++i)
    {
        allPlainText += DESEncryption(stdPlainText.substr(i*64, 64), keys).toStdString();
    }

    return QString::fromStdString(binaryAsciiToText(allPlainText));
}

std::vector< std::string > MainWindow::textToBinaryAscii(std::string str)
{
    std::vector< std::string > blocksOfData;

    for(int i=0; i<str.size()/8; ++i)
    {
        std::string blockStr = str.substr(i*8, 8);
        std::string block = "";

        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);

        blocksOfData.push_back(block);
    }

    if(str.size()%8 != 0)
    {
        int start = ((int)str.size()/8)*8;
        int length = (int)str.size()- start;

        std::string blockStr = str.substr(start, length);
        for(int i=0; i<(8-length); ++i)
            blockStr += " ";

        std::string block = "";
        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);
        blocksOfData.push_back(block);
    }

    return blocksOfData;
}

std::string MainWindow::binaryAsciiToText(std::string str)
{
    std::string blocksOfData = "";

    for(int i=0; i<str.size()/64; ++i)
    {
        std::string blockStr = str.substr(i*64, 64);
        std::string block = "";

        for(int i=0; i<8; ++i)
        {
           std::string ascii = blockStr.substr(i*8, 8);
           block += binaryAsciiToChar(ascii);
        }
        blocksOfData += block;
    }

    return blocksOfData;
}

std::string MainWindow::charToBinaryAscii(char ch)
{
    return std::bitset<8>(int(ch)).to_string();
}

char MainWindow::binaryAsciiToChar(std::string binaryAscii)
{
    return char(std::bitset<8>(binaryAscii).to_ulong());
}





// RSA Methods

double MainWindow::ewRSA(double msg, double p, double q)
{
    // generate public as first, private as second key
    std::pair<double,double> keys = RSAKeys(p, q);

    double n = p*q;
    double e = keys.first;

    return RSAEncryption(msg, n, e);
}

double MainWindow::dwRSA(double msg, double p, double q)
{
    // generate public as first, private as second key
    std::pair<double,double> keys = RSAKeys(p, q);

    int n = p*q;
    int d = keys.second;

    return RSADecryption(msg, n, d);
}

double MainWindow::RSAEncryption(double msg, double n, double e)
{
    // Encryption c = (msg ^ e) % n
    double c = pow(msg, e);
    c = fmod(c, n);
    return c;
}

double MainWindow::RSADecryption(double msg, double n, double d)
{
    // Decryption m = (c ^ d) % n
    double m = pow(msg, d);
    m = fmod(m, n);
    return m;
}

std::pair<double, double> MainWindow::RSAKeys(double p, double q)
{
    // Finding public key; e stands for encrypt.
    double e = 2;
    double phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient

    int d = e;
    while((int)(d*e)%((int)phi) != 1)
    {
        d++;
    }

    return std::make_pair(e, d);
}

int MainWindow::gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}





// RC4 Methods

QString MainWindow::ewRC4(QString msg, QString key)
{
    std::vector<int> k;

    // initialize key
    std::string stdCppKey = key.toStdString();
    for(int i=0; i<stdCppKey.length(); ++i)
        k.push_back(int(stdCppKey[i] - '0'));

    std::vector<int> s(256);
    std::vector<int> t(256);

    // initialize vector S to [0:255]
    for(int i=0; i<256; ++i)
        s[i] = i;

    // initialize vector T from key K
    for(int i=0; i<256; ++i)
        t[i] = k[i%k.size()];

    // initial Permutation Of S
    int j = 0;
    for(int i=0; i<256; ++i)
    {
        j = (j + s[i] + t[i])%256;
        std::swap(s[i], s[j]);
    }

    // prepare msg
    std::vector< std::bitset<8> > msg_bytes = bytesOfMessage(msg.toStdString());


    // generate a key for each byte of input
    // e.g input: 5 bytes, generates output: 5 bytes
    std::vector< std::bitset<8> > keys = keysGenerator((int)msg_bytes.size(), s);

    return RC4Encryption(msg_bytes, keys);

}

QString MainWindow::dwRC4(QString msg, QString key)
{
    return ewRC4(msg, key);
}

QString MainWindow::RC4Encryption(std::vector< std::bitset<8> > msg_bytes, std::vector< std::bitset<8> > keys)
{
    std::string result = "";
    for (int i = 0; i < msg_bytes.size(); ++i)
    {
        std::bitset<8> temp = std::bitset<8>(msg_bytes[i] ^ keys[i]);
        result += temp.to_string();
    }

    // Debugging output
    /*std::cout << "> Debugging Statements" << std::endl;

    std::cout << "I/P: " ;
    for(int t=0; t<msg_bytes.size(); ++t)
        std::cout << msg_bytes[t];
    std::cout << std::endl;

    std::cout << "Key: ";
    for(int t=0; t<keys.size(); ++t)
        std::cout << keys[t].to_string();
    std::cout << std::endl;
    std::cout << "O/P: " << result << std::endl;*/

    return QString::fromStdString(result);
}

std::vector< std::bitset<8> > MainWindow::keysGenerator(int msg_length, std::vector<int> s)
{
    std::vector< std::bitset<8> > keys(msg_length);

    int i=0, j=0, k=0;
    for (int lc = 0; lc < msg_length; ++lc)
    {
        i = (i+1)%256;
        j = (j+s[i])%256;
        std::swap(s[i], s[j]);
        k = s[(s[i]+s[j])%256];
        keys[lc] = std::bitset<8>(k);
    }

    return keys;
}

std::vector< std::bitset<8> > MainWindow::bytesOfMessage(std::string msg)
{
    std::vector< std::bitset<8> > msg_bytes;

    for(int i=0; i<(msg.length()/8); ++i)
    {
        std::string msg_byte = "";
        for(int j=0; j<8; ++j)
        {
            int idx = j + i*8;
            msg_byte += msg[idx];
        }
        msg_bytes.push_back(std::bitset<8>(msg_byte));
    }

    return msg_bytes;
}









void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate datee=ui->calendarWidget->selectedDate();
            qDebug() << datee;
            QDate d= datee;
            qDebug() << d;
            QSqlQuery query;
            query.prepare("SELECT id,nom,prenom,type_immatriculation,numImmatriculation,date_res FROM reservation WHERE  date_res=:date");
            query.bindValue(":date",d);
            query.exec();
            QSqlQueryModel * model=new QSqlQueryModel();


                  model->setQuery(query);
                  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                  model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                  model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_immatriculation"));
                  model->setHeaderData(4, Qt::Horizontal, QObject::tr("numImmatriculation"));
                  model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_res"));


                 ui->calendrier->setModel(model);
}
