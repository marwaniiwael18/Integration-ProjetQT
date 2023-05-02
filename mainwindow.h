#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include<QMessageBox>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDialog>
#include <QSettings>
#include <QDataStream>
#include <QStandardItemModel>

#include <QSettings>
#include <QPainter>
#include <QDesktopServices>
#include <QTextDocument>
#include <QFileDialog>
#include <QPdfWriter>
#include <QtDebug>
#include <QDesktopWidget>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QDataStream>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QPrinter>
#include<QtCharts/QPieSeries>
#include<QPieSlice>
#include<QtCharts>
#include<QChartView>
#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QMessageBox>
#include<QIntValidator>
#include <QApplication>
#include<QSound>
#include<QDebug>
#include<QMediaPlayer>
#include <QPrinter>
#include <QTextStream>
#include <QTextDocument>
#include <QDataStream>
#include <QPrintDialog>
#include <QSqlQuery>
#include<QComboBox>
#include<QSaveFile>
#include<QBuffer>
#include<QFileDialog>
#include<QFile>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include<QDesktopServices>
#include<QUrl>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include<QGraphicsView>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QDate>
#include <QTime>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QDateEdit>
#include<QFileDialog>
#include"smtp.h"
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
#include <QPainter>
#include<QString>
#include<QStatusBar>
#include<QTimer>
#include<QDateTime>
#include <QSqlError>
#include<QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include<QRegExpValidator>
#include<QVBoxLayout>
#include<QMenu>
#include<QAction>
#include <bitset>
#include <QtNetwork/QAbstractSocket>
#include <string>
#include <cstring>
#include <sstream>

#include "employees_statistiques.h"
#include "connection.h"
#include "employee.h"
#include "piste.h"
#include "captchabox.h"
#include "vehicule.h"
#include "qrcode.h"
#include"smtp.h"
#include "equipement.h"
#include "exportexcelobject.h"
#include "ardBarriere.h"
#include "ardPorte.h"
#include "reservation.h"
#include "calendrier.h"
#include "visite.h"
#include "notifications.h"

QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
struct Position
{
    int x;
    int y;
};

class QTcpSocket;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

        int m_currentPage = 0;
        const int m_pageSize = 3;
        //QSortFilterProxyModel* proxyModel;
        QStandardItemModel *model;

private slots:
    void on_Login_push_Login_clicked();

    void on_Menu_push_Employees_clicked();
    void on_Menu_push_Equipements_clicked();
    void on_Menu_push_Pistes_clicked();
    void on_Menu_push_Vehicules_clicked();
    void on_Menu_push_Reservations_clicked();
    void on_Menu_push_Reture_clicked();
    void on_Menu_push_Quitter_clicked();
    void on_Empl_push_Ajouter_clicked();

    void on_Empl_push_Modifier_2_clicked();

    void on_Empl_push_Supprimer_clicked();

    void on_pb_rechercher_clicked();

    void on_Empl_line_Recherche_textChanged(const QString &arg1);

    void on_Empl_push_TriSalire_clicked();

    void on_Empl_push_TriPoste_clicked();

    void on_Empl_push_TriNom_clicked();

    void on_Empl_push_ExportPDF_clicked();

    void on_Empl_push_Send_clicked();

    void on_Empl_push_Bind_clicked();

    void on_Empl_push_Statistiques_clicked();

    void on_Empl_push_reture_clicked();

    void on_Menu_push_Visits_clicked();





    void on_Piste_push_reture_clicked();

    void on_pb_modifier_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_rechercher_3_clicked();

    void on_Empl_push_ExportPDF_3_clicked();

    void on_triID_clicked();

    void on_ID_desc_clicked();

    void on_triID_2_clicked();

    void on_trinumPistedesc_clicked();

    void on_tritype_clicked();

    void on_tritypedesc_clicked();

    void on_pushButton_2_clicked();

    void on_btn_add_clicked();

    void on_Empl_push_Statistiques_4_clicked();



    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pb_modifier_2_clicked();

    void on_pushButton_rechercher_clicked();

    void on_pushButton_PDF_clicked();

    void on_triID_3_clicked();

    void on_nom_az_clicked();

    void on_nom_desc_clicked();

    void on_ID_desc_2_clicked();

    void on_qrcodegen_2_clicked();

    void on_pushButton_3_clicked();

    void on_moisuivant_clicked();

    void on_moisprec_clicked();

    void addPagination();


    void on_Empl_push_reture_2_clicked();

    void on_trimodele_clicked();

    void on_tritypedesc_2_clicked();

    void on_pb_ajouter_3_clicked();

    void on_pb_supprimer_3_clicked();

    void on_pb_modifier_3_clicked();

    void on_pushButton_rechercher_2_clicked();

    void on_pushButton_PDF_2_clicked();

    void on_triID_4_clicked();

    void on_nom_az_2_clicked();

    void on_nom_az_3_clicked();

    void on_ID_desc_3_clicked();

    void on_export_excel_clicked();

    void on_sendBtn_clicked();

    void on_browseBtn_clicked();

    void on_pushButton_4_clicked();

    void on_Empl_push_reture_3_clicked();




    void update_label_1();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void update_label_2();




    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_Reserv_retour_clicked();

    void on_Visites_retour_clicked();

    void on_pb_ajouter_4_clicked();

    void on_pb_modifier_4_clicked();

    void on_pb_supprimer_4_clicked();

    void on_pb_rechercher_2_clicked();

    void on_triID_5_clicked();

    void on_ID_desc_4_clicked();





    void on_Empl_push_ExportPDF_2_clicked();

    void on_Empl_push_Statistiques_2_clicked();





    void on_aff_clicked();

    void on_supphistorique_clicked();

    void on_supphistorique_2_clicked();

    void on_pdfhistorique_clicked();

    void on_tableView_his_activated(const QModelIndex &index);



    void on_pb_ajouter_5_clicked();

    void on_pb_modifier_5_clicked();

    void on_pb_supprimer_5_clicked();

    void on_pb_rechercher_4_clicked();

    void on_pushButton_PDF_3_clicked();

    void on_statsmed_clicked();

    void on_triID_6_clicked();

    void on_ID_desc_5_clicked();

    void on_pushButton_encrypt_clicked();
    void on_actionReset_Fields_triggered();
    void on_actionClear_Plain_Text_triggered();
    void on_actionClear_Encrypted_Text_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_Qt_triggered();
    void on_comboBox_currentTextChanged(const QString &arg1);


    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;

    QString tmpemail;
    Employee E;
    Piste P;
    CaptchaBox *captchaBox;
    Vehicule v;
    Vehicule *ve;
    Equipement Q;
    Reservation R;
    Visite s;
    Visite *se;

    QTcpSocket *nSocket;
    Employees_Statistiques *stat;

    //music
    QStandardItemModel  *m_playListModel;   // Модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // Проигрыватель треков
    QMediaPlaylist      *m_playlist;

      QStringList files;

      quint16 mport=3333;
      QString mnomemp="localhost";
      QTcpSocket *mSocket;

      Arduino A;
      Arduinoo B;// objet temporaire
      QByteArray data; // variable contenant les données reçues

      bool dateTimeEditS_hadfocus = false;
      bool dateTimeEditE_hadfocus = false;

      QString ewCaesarCipher(QString plainText, int key);
          QString dwCaesarCipher(QString encryptedText, int key);

          QString ewPlayfair(QString plainText, QString secret);
          QString dwPlayfair(QString encryptedText, QString secret);

          char pfMatrix[5][5];
        bool inSameRow(Position p1, Position p2);
       bool inSameColumn(Position p1, Position p2);
          void normalizePFString(std::string &str);
          void normalizePFSecret(std::string &secret);
          void populatePFMatrix(std::string secret);
          std::string encryptPFString(std::string plainStdText);
          std::string decryptPFString(std::string encryptedStdText);
         Position findPositionByChar(char ch);
          char findCharByPosition(Position p);

          QString ewDES(QString plainText, std::string key);
          QString dwDES(QString encryptedText, std::string key);
          std::vector<std::string> keyPreparation(std::string key);
          QString DESEncryption(std::string dataBlock, std::vector< std::string > keys);
          std::string apply_xor(std::string str1, std::string str2);
          std::string apply_func_F(std::string str1, std::string str2);
          std::string apply_func_E(std::string str);

          QString ewIDES(QString plainText, std::string key);
          QString dwIDES(QString encryptedText, std::string key);
          std::vector< std::string > textToBinaryAscii(std::string str);
          std::string binaryAsciiToText(std::string str);
          std::string charToBinaryAscii(char ch);
          char binaryAsciiToChar(std::string binaryAscii);

          double ewRSA(double msg, double p, double q);
          double dwRSA(double msg, double p, double q);
          double RSAEncryption(double msg, double n, double e);
          double RSADecryption(double msg, double n, double d);
          std::pair<double, double> RSAKeys(double p, double q);
          int gcd(int a, int h);

          QString ewRC4(QString msg, QString key);
          QString dwRC4(QString msg, QString key);
          QString RC4Encryption(std::vector< std::bitset<8> > msg_bytes, std::vector< std::bitset<8> > keys);
          std::vector< std::bitset<8> > keysGenerator(int msg_length, std::vector<int> s);
          std::vector< std::bitset<8> > bytesOfMessage(std::string msg);

};
#endif // MAINWINDOW_H
