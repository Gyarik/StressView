#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("StressView"));
    listWidget = new SensorListWidget(this);

    hor = new QSplitter;
    vert = new QSplitter;

    hor->setChildrenCollapsible(false);
    vert->setChildrenCollapsible(false);
    vert->setOrientation(Qt::Vertical);
    vert->addWidget(listWidget);

    QList<int> sz;
    sz << 100 << 300;
    vert->setSizes(sz);
    this->setCentralWidget(vert);

    connect(listWidget, &SensorListWidget::nameCpy, this, &MainWindow::printInfo);
    connect(listWidget, &SensorListWidget::tryNew, this, &MainWindow::onTryNew);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slots

void MainWindow::printInfo(GenericSensor *sen)
{
    if(!sen)
    {
        qDebug() << "ERROR: sensor = nullptr";
        return;
    }
}

void MainWindow::onTryNew()
{

}
