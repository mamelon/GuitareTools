#include "menubar.h"
#include "ui_menubar.h"

MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuBar)
{
    ui->setupUi(this);
}

MenuBar::~MenuBar()
{
    delete ui;
}

void MenuBar::on_homePushButton_clicked()
{
    emit home();
}

void MenuBar::on_toolsPushButton_clicked()
{
    emit tools();
}

void MenuBar::on_quitPushButton_clicked()
{
    emit quit();
}

void MenuBar::on_tunerPushButton_clicked()
{
    emit tuner();
}

void MenuBar::on_metronomePushButton_clicked()
{
    emit metronome();
}
