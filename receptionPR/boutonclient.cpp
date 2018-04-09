#include "boutonclient.h"

BoutonClient::BoutonClient(QString leClient,QString nomCli, QWidget *parent) :client(leClient),
    QPushButton(parent)
{
    sonTableWidget=NULL;
    open=false;
}

QString BoutonClient::getClient()
{
    return client;
}

QTableWidget* BoutonClient::getTabAdresse()
{
    return sonTableWidget;
}

bool BoutonClient::isOpen()
{
    return open;
}

void BoutonClient::setTableWidget(QTableWidget *leTableWidget)
{
    sonTableWidget=leTableWidget;
    open=true;
}
