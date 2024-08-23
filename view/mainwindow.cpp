#include "mainwindow.h"
#include "ui_mainwindow.h"

SensorContainer *MainWindow::list = new SensorContainer();
Visitor *MainWindow::visitor = new Visitor();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("StressView"));
    listWidget = new SensorListWidget(this);
    infoWidget = new SensorInfoWidget(this);

    hor = new QSplitter;
    vert = new QSplitter;

    hor->setChildrenCollapsible(false);
    vert->setChildrenCollapsible(false);
    vert->setOrientation(Qt::Vertical);
    vert->addWidget(infoWidget);
    hor->addWidget(listWidget);
    hor->addWidget(vert);
    hor->setHandleWidth(10);
    vert->setHandleWidth(10);

    QList<int> sz;
    sz << 100 << 330;
    vert->setSizes(sz);
    this->setCentralWidget(hor);

    connect(listWidget, &SensorListWidget::nameCpy, this, &MainWindow::printInfo);
    connect(listWidget, &SensorListWidget::tryNew, this, &MainWindow::onTryNew);

    connect(vert, &QSplitter::splitterMoved, this, [this](int p)
    {
        if(p < threshold)
            isSplitterGood = false;
        else
            isSplitterGood = true;
    });
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
    infoWidget->setName(QString::fromStdString(sen->getName()));
    infoWidget->setDesc(QString::fromStdString(sen->getDesc()));
    infoWidget->setBounds(QString::number(sen->getMax()), QString::number(sen->getTemp()));
    sen->accept(visitor);
    infoWidget->setComponent(QString::fromStdString(visitor->getType()));

    if(!isSplitterGood)
    {
        QList<int> nsz;
        nsz << 100 << 330;
        vert->setSizes(nsz);
    }
}

void MainWindow::onTryNew()
{
    AddSensor *addWidget = new AddSensor();
    addWidget->show();
    connect(addWidget, &AddSensor::infoExists, this, &MainWindow::onNewAddable);
}

void MainWindow::onNewAddable(GenericSensor *sen)
{
    if(MainWindow::list->addSensor(sen))
        listWidget->newButton(sen, visitor);
    else
    {
        ErrorWindow *Error = new ErrorWindow("Cannot create sensor: Name already in use", this);
        Error->show();
    }
}
