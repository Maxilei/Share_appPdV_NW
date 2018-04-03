#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include<QNetworkAccessManager>
#include<QJsonArray>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QNetworkAccessManager *pmyNWM,QString theName, QString theSurname, QString theMail, QWidget *parent = 0 );
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString name,surname,mail;
    QNetworkReply *reply;
    QJsonArray jsArray;
    QNetworkAccessManager * myNWM;
public slots:
    void afficheLesProducteurs();
    void afficheLaLivraison();
};

#endif // MAINWINDOW_H
