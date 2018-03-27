#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);
    myNWM.setCookieJar(&cookieJar);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_pushButtonOk_clicked()
{

}

void DialogLogin::on_pushButtonCancel_clicked()
{
    reject();
}
