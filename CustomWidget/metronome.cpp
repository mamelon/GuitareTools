#include "metronome.h"
#include "ui_metronome.h"

#include "Tools/lecture.h"


#include <QTimer>
#include <QDebug>
#include <QSound>
#include <QFile>

Metronome::Metronome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Metronome)
{
    ui->setupUi(this);
    playing = false;
    leftLedOn = false;
    timerLed = new QTimer(this);
    timerNeedle = new QTimer(this);

    initInterface();
}

Metronome::~Metronome()
{
    delete scene;
    delete leftLed;
    delete rightLed;
    delete aiguille;
    delete bottomLine;
    delete timerLed;
    delete timerNeedle;
    delete ui;
}

void Metronome::initInterface()
{

//    beatBar = new QProgressBar(this);
//    beatBar->setMaximum(0);
//    beatBar->setMaximum(180);

    /* Init the Dial to change tempo */
    ui->tempoDial->setMaximum(300);
    ui->tempoDial->setMinimum(100);
    ui->tempoDial->setValue(120);
    ui->tempoLcdNumber->display(120);
    connect(ui->tempoDial,SIGNAL(valueChanged(int)),SLOT(changeTempo(int)));

    /* Init the Play and Stop Button */
    connect(ui->playAndStopPushButton,SIGNAL(clicked()),SLOT(togglePlayStopButton()));

    /* Init the scene */
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,400,300);
    resetInterfaceComp();
    ui->viewScene->setScene(scene);
    ui->viewScene->show();
}

void Metronome::play()
{
    playing = true;
//    QFile::exists("sons/kick.wav") ? qDebug()<<"chemin ok" : qDebug()<<"chemin nok";
//    Lecture::instance()->play("sons/kick.ogg");
    ui->playAndStopPushButton->setIcon(QIcon(":/icones/images/stop.png"));
    leftLedOn = true;
    leftLed->setPixmap(QPixmap(":/icones/images/greenLedOn.png"));
    bpm = ui->tempoDial->value();

    timerLed->start(60000/bpm);
    qDebug() << "led interval " << timerLed->interval();
    timerNeedle->start(180/bpm*60000);
    qDebug() << "needle interval " << timerNeedle->interval();
    connect(timerLed,SIGNAL(timeout()),SLOT(changeState()));
    connect(timerNeedle,SIGNAL(timeout()),SLOT(animeNeedle()));



}

void Metronome::stop()
{
    playing = false;

    scene->removeItem(leftLed);
    scene->removeItem(rightLed);
    scene->removeItem(aiguille);

    ui->playAndStopPushButton->setIcon(QIcon(":/icones/images/play.png"));
    leftLed->setPixmap(QPixmap(":/icones/images/greenLedOff.png"));
    rightLed->setPixmap(QPixmap(":/icones/images/greenLedOff.png"));
    timerLed->stop();
    timerNeedle->stop();
    cptNeedle = 0;

    resetInterfaceComp();

}

void Metronome::changeTempo(int bpm)
{
    ui->tempoLcdNumber->display(bpm);
    timerLed->setInterval(60000/bpm); //change tempo whereas we're already playing.
}

void Metronome::togglePlayStopButton()
{
    if(!playing) play();
    else stop();
}

void Metronome::changeState()
{
//    Lecture::instance()->stop();
//    Lecture::instance()->play("sons/kick.ogg");
    if(leftLedOn)
    {
        leftLedOn = false;
        leftLed->setPixmap(QPixmap(":/icones/images/greenLedOff.png"));
        rightLed->setPixmap(QPixmap(":/icones/images/greenLedOn.png"));
    }
    else{
        leftLedOn = true;
        leftLed->setPixmap(QPixmap(":/icones/images/greenLedOn.png"));
        rightLed->setPixmap(QPixmap(":/icones/images/greenLedOff.png"));
    }

}

void Metronome::animeNeedle()
{
    if(cptNeedle==180)
        needleToRight = false;
    if(cptNeedle==0)
        needleToRight = true;

    if(needleToRight && cptNeedle <180)
         cptNeedle ++;
    if(!needleToRight && cptNeedle >0)
        cptNeedle --;



    qDebug() << cptNeedle;
    aiguille->setTransform(QTransform().translate(scene->width()/2,scene->height()).rotate(1).translate(-scene->width()/2,-scene->height()), true);

}

void Metronome::resetInterfaceComp()
{
    /* Init the needle */
    cptNeedle = 0;
    needleToRight = true;

    leftLed = scene->addPixmap(QPixmap(":/icones/images/greenLedOff.png"));
    rightLed = scene->addPixmap(QPixmap(":/icones/images/greenLedOff.png"));
    qDebug() << scene->width() << "x" << scene->height();
    aiguille = scene->addLine(scene->width()/2,scene->height(),40,scene->height(),QPen(QColor(77,77,255)));
    leftLed->setPos(0,scene->height()-32);
    rightLed->setPos(scene->width()-32,scene->height()-32);
    aiguille->setTransformOriginPoint(QPointF(scene->width()/2,scene->height()));
    qDebug() << "Point d'origine des transformation de aiguile " << aiguille->transformOriginPoint();
    qDebug() << aiguille->transformOriginPoint();

}




