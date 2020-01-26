#include "mainwindow.h"
#include "theory.h"
#include "demo.h"
#include "test.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->demoBnt, SIGNAL(clicked()), this, SLOT(demoBtn_Clicked()));
    connect(ui->testBtn, SIGNAL(clicked()), this, SLOT(testBtn_Clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::theoryBtn_Clicked()
{
    Theory theory;
    theory.setModal(true);
    theory.exec();
}

void MainWindow::demoBtn_Clicked()
{
    Demo demo;
    demo.setModal(true);
    demo.exec();
}

void MainWindow::testBtn_Clicked()
{
    Test test;
    test.setModal(true);
    test.exec();
}
