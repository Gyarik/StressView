#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("StressView"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_simButton_clicked()
{

}

