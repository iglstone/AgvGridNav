#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->plot = new plotter;
    this->setCentralWidget(this->plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
