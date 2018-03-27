#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();
<<<<<<< HEAD
    QString identifiant,nom,prenom;
    QNetworkAccessManager myNWM;
    QNetworkCookieJar cookieJar;
private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();
=======
>>>>>>> 4d78c2a765b6c59af00abfae8589a4f96fd12b2c

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
