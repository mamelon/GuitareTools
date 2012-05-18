#include "accordeur.h"
#include "ui_accordeur.h"


Accordeur::Accordeur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Accordeur)
{
    ui->setupUi(this);

    ui->frequencyLevelprogressBar->setValue(0);
    ui->frequencyLevelprogressBar->setTextVisible(false);

    connect(ui->MiGravepushButton,SIGNAL(clicked()),SLOT(MiGrave()));
    connect(ui->LapushButton,SIGNAL(clicked()),SLOT(La()));
    connect(ui->RepushButton,SIGNAL(clicked()),SLOT(Re()));
    connect(ui->SolpushButton,SIGNAL(clicked()),SLOT(Sol()));
    connect(ui->SipushButton,SIGNAL(clicked()),SLOT(Si()));
    connect(ui->MiAiguepushButton,SIGNAL(clicked()),SLOT(MiAigue()));

}

Accordeur::~Accordeur()
{
    delete ui;
}

void Accordeur::MiGrave()
{
    freq2Test = 82.4;
}

void Accordeur::La()
{
    freq2Test = 110.0;
}

void Accordeur::Re()
{
    freq2Test = 146.8;
}

void Accordeur::Sol()
{
    freq2Test = 196.0;
}

void Accordeur::Si()
{
    freq2Test = 246.9;
}

void Accordeur::MiAigue()
{
    freq2Test = 329.6;
}

void Accordeur::ecouter()
{
    qDebug() << "[Listen] Start....";
}

void Accordeur::arreterEcoute()
{
    qDebug() << "[Listen] Stop...."
}
