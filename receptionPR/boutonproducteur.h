#ifndef BOUTONPRODUCTEUR_H
#define BOUTONPRODUCTEUR_H

#include <QPushButton>
#include <QTableWidget>
#include <QObject>

class BoutonProducteur : public QPushButton
{
    Q_OBJECT
private:
    QTableWidget* sonTableWidget;
    bool ouvert;
    QString producteur;
public:
    explicit BoutonProducteur(QString leProducteur,QString nomProd, QWidget *parent = 0);

signals:

public slots:
    QString getProducteur();
    QTableWidget* getTabAdresse();
    bool estOuvert();
    void setTableWidget(QTableWidget* leTableWidget);

};

#endif // BOUTONPRODUCTEUR_H
