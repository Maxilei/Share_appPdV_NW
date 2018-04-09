#ifndef BOUTONCLIENT_H
#define BOUTONCLIENT_H

#include <QPushButton>
#include <QTableWidget>
#include <QObject>

class BoutonClient : public QPushButton
{
    Q_OBJECT
private:
    QTableWidget* sonTableWidget;
    bool open;
    QString client;
public:
    explicit BoutonClient(QString leClient,QString nomCli, QWidget *parent = 0);

signals:

public slots:
    QString getClient();
    QTableWidget* getTabAdresse();
    bool isOpen();
    void setTableWidget(QTableWidget* leTableWidget);

};

#endif // BOUTONCLIENT_H
