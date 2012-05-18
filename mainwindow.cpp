#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CustomWidget/menubar.h"
#include "CustomWidget/accordeur.h"

#include "Tools/capture.h"

#include <QDebug>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->IndexStackedWidget->setCurrentIndex(0);

    connect(ui->MenBarWidget,SIGNAL(tools()),SLOT(on_actionP_riph_riques_de_capture_triggered()));
    connect(ui->MenBarWidget,SIGNAL(home()),SLOT(home()));
    connect(ui->MenBarWidget,SIGNAL(quit()),SLOT(on_actionQuitter_triggered()));
    connect(ui->MenBarWidget,SIGNAL(tuner()),SLOT(tuner()));
    connect(ui->MenBarWidget,SIGNAL(metronome()),SLOT(metronome()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::home()
{
    ui->IndexStackedWidget->slideInIdx(0,SlidingStackedWidget::RIGHT2LEFT);
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionP_riph_riques_de_capture_triggered()
{
    ui->peripheriqueListWidget->clear();
    ui->IndexStackedWidget->slideInIdx(3,SlidingStackedWidget::LEFT2RIGHT);
    foreach(QString s,Capture::getCaptureDevices())
        new QListWidgetItem(s,ui->peripheriqueListWidget);

}

void MainWindow::tuner()
{
    ui->IndexStackedWidget->slideInIdx(1,SlidingStackedWidget::LEFT2RIGHT);
}

void MainWindow::metronome()
{
    ui->IndexStackedWidget->slideInIdx(2,SlidingStackedWidget::LEFT2RIGHT);
}
