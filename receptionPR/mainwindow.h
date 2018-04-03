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
    explicit MainWindow(QNetworkAccessManager *pmyNWM,QString theName, QString theSurname, QString theIdentifiant, QWidget *parent = 0 );
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString name,surname,id;
    QNetworkReply *reply;
    QJsonArray jsArray;
    QNetworkAccessManager * myNWM;

};

#endif // MAINWINDOW_H
