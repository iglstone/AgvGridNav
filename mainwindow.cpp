#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

//    carNavAlgrithm *graphSearch = new carNavAlgrithm();


    this->plot = new plotter;
    this->setCentralWidget(this->plot);


/*
    Serial485 *se = new Serial485();
    QString st = "COM3";

    se->open_device(st);
    unsigned char *ch = (unsigned char*)"1234567";
    se->write_com(ch,7);
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}
