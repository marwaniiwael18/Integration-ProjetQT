#include "notifications.h"


void notification::notification_ajout()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/Desktop/new visit.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("smart technical center"," une nouvelle visite a été ajouter !",QSystemTrayIcon::Information,15000);

}
