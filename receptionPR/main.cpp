#include "mainwindow.h"
#include <QApplication>
#include <QtNetwork>
#include "dialoglogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogLogin dialogLogin;
    dialogLogin.setWindowState(dialogLogin.windowState()|Qt::WindowFullScreen);//or WindowMaximized
    if(dialogLogin.exec()==QDialog::Accepted)
    {
        MainWindow w(&dialogLogin.myNWM,dialogLogin.nom,dialogLogin.prenom,dialogLogin.mail);
        w.show();
        return a.exec();
    }
    else
        return(-1);

}
