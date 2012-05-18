#ifndef ACCORDEUR_H
#define ACCORDEUR_H

#include <QWidget>
#include <QFile>

#include <phonon>

namespace Ui {
class Accordeur;
}

namespace QAudio{
class QAudio;
}

class Accordeur : public QWidget
{
    Q_OBJECT
    
public:
    explicit Accordeur(QWidget *parent = 0);
    ~Accordeur();

    void ecouter();
    void arreterEcoute();
private slots:
    void MiGrave();
    void La();
    void Re();
    void Sol();
    void Si();
    void MiAigue();
    
private:
    Ui::Accordeur *ui;
    double freq2Test;
    QFile * fichierDeSortie;
};

#endif // ACCORDEUR_H
