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

    vertSplit = new QSplitter;
    horSplit = new QSplitter;

    vertSplit->setChildrenCollapsible(false);
    horSplit->setChildrenCollapsible(false);
    horSplit->setOrientation(Qt::Vertical);
    vertSplit->addWidget(horSplit);
    horSplit->addWidget(infoWidget);
    vertSplit->addWidget(listWidget);
    // vertSplit->setHandleWidth(10);
    // horSplit->setHandleWidth(10);

    QList<int> sz;
    sz << 100 << 330;
    vertSplit->setSizes(sz);
    this->setCentralWidget(vertSplit);

    connect(listWidget, &SensorListWidget::nameCpy, this, &MainWindow::printInfo);
    connect(listWidget, &SensorListWidget::tryNew, this, &MainWindow::onTryNew);
    connect(listWidget, &SensorListWidget::removedSensor, this, &MainWindow::onRemovedSensor);
    connect(listWidget, &SensorListWidget::clearedList, this, &MainWindow::onClearedList);

    connect(infoWidget, &SensorInfoWidget::editSensor, this, &MainWindow::onEditSensor);
    //connect(infoWidget, &SensorInfoWidget::clearSensor, this, &MainWindow::onClearSensor());

    connect(vertSplit, &QSplitter::splitterMoved, this, [this](int p)
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
        vertSplit->setSizes(nsz);
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

void MainWindow::onRemovedSensor()
{
    listWidget->setCurrent(nullptr);
    infoWidget->resetFields();
}

void MainWindow::onClearedList()
{
    listWidget->setCurrent(nullptr);
    list->emptyContainer();
    infoWidget->resetFields();
}

void MainWindow::onEditSensor()
{
    if(listWidget->getCurrent() != nullptr)
    {
        GenericSensor *sensor = listWidget->getCurrent();
        prevName = sensor->getName();
        editWidget = new ModifySensor(sensor);
        editWidget->show();

        connect(editWidget, &ModifySensor::changeSensor, this, &MainWindow::onChangeSensor);
        connect(this, &MainWindow::canEdit, editWidget, &ModifySensor::onCanEdit);
        connect(editWidget, &ModifySensor::refreshInfo, this, &MainWindow::onRefreshInfo);
    }
}

void MainWindow::onChangeSensor()
{
    string cur = editWidget->getName();
    if(!MainWindow::list->isEqual(cur, prevName))
        emit canEdit();
    else
    {
        ErrorWindow *Error = new ErrorWindow("Sensor with the same name already exists");
        Error->show();
    }
}

void MainWindow::onRefreshInfo(const GenericSensor *sen, const string &prev)
{
    infoWidget->setName(QString::fromStdString(sen->getName()));
    infoWidget->setDesc(QString::fromStdString(sen->getDesc()));
    infoWidget->setBounds(QString::number(sen->getMax()), QString::number(sen->getTemp()));
    listWidget->changeButton(sen->getName(), prev);
}
