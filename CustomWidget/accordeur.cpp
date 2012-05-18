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
       fichierDeSortie = new QFile("piste_Audio.raw"); // specifier un nom pour le fichier enregistrer
       fichierDeSortie->open(QIODevice::WriteOnly | QIODevice::Truncate); // ouvrire en ecriture seule et coupure prématuré du fichier si besoin

       QAudioFormat format; //creer une variable de type QAudioFormat

       // configurer le format ...
       format.setFrequency(FREQUENCE_ECHANTILLON); // specifier la frequence d'échantillonage
       format.setChannels(1); // specifier le canal d'écoute
       format.setSampleSize(8); // specifier la taille des données stoqué dans chaque echantillon 8 ou 16 bits
       format.setCodec("audio/pcm"); // specifier le codec à utiliser
       format.setByteOrder(QAudioFormat::LittleEndian); // specifier l'ordre de rangement des bits
       format.setSampleType(QAudioFormat::UnSignedInt); // specifie le type de variable du tableau d'echantillonage

        QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice()); // creation d'un info ...
           if (!info.isFormatSupported(format)) // si le format n'est pas supporté ...
           {
               qDebug() << "Le format par spécifié pour l'enregistrement n'est pas supporté, utilisation d'un format plus récent."; // afficher le message dans la box ... à supprimé
               format = info.nearestFormat(format); // utiliser un autre format ... plus récent ...
           }

       audio = new QAudioInput(format, this);
        QTimer::singleShot(TPS_ENREGISTREMENT*1000, this, SLOT(arreterEcoute())); // Qtimer définisant le temps d'écoute
       audio->start(fichierDeSortie);
       // Records audio for 5000ms

       qDebug() << "debut d'enregistrement ... "+ QString::number(TPS_ENREGISTREMENT) +" secondes."; // afficher le message dans la box ... à supprimé
}

void Accordeur::arreterEcoute()
{
   audio->stop(); // arreter l'enregistrement
   fichierDeSortie->close(); // fermer le fichier ...
   delete audio; // supprimer la variable audio
}
