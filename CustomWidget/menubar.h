#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>

namespace Ui {
class MenuBar;
}

class MenuBar : public QWidget
{
    Q_OBJECT
    
public:
    explicit MenuBar(QWidget *parent = 0);
    ~MenuBar();
    
signals:
    void home();
    void tools();
    void tuner();
    void metronome();
    void quit();

private slots:
    void on_homePushButton_clicked();
    void on_toolsPushButton_clicked();
    void on_quitPushButton_clicked();
    void on_tunerPushButton_clicked();
    void on_metronomePushButton_clicked();

private:
    Ui::MenuBar *ui;
};

#endif // MENUBAR_H
