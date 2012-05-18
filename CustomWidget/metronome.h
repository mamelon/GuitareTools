#ifndef METRONOME_H
#define METRONOME_H

#include <QSound>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>



namespace Ui {
class Metronome;
}

class Metronome : public QWidget
{
    Q_OBJECT
    
public:
    explicit Metronome(QWidget *parent = 0);
    ~Metronome();

private:
    void initInterface();
    void play();
    void stop();

private slots:
    void changeTempo(int bpm);
    void togglePlayStopButton();
    void changeState();
    void animeNeedle();
    void resetInterfaceComp();

private:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *leftLed;
    QGraphicsPixmapItem *rightLed;
    QGraphicsLineItem *aiguille;
    QGraphicsLineItem *bottomLine;
    QTimer * timerLed;
    QTimer * timerNeedle;
    int cptNeedle;
    bool playing;
    bool leftLedOn;
    bool needleToRight;
    int bpm;
    Ui::Metronome *ui;
};

#endif // METRONOME_H
