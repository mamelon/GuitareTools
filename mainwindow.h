#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void home();
    void on_actionQuitter_triggered();
    void on_actionP_riph_riques_de_capture_triggered();
    void tuner();
    void metronome();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
