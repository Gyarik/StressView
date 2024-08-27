#include "mainwindow.h"
#include "ui_mainwindow.h"

SensorContainer *MainWindow::list = new SensorContainer();
Visitor *MainWindow::visitor = new Visitor();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("StressView"));
    this->setWindowIcon(QIcon(":/icons/resources/app.png"));
    listWidget = new SensorListWidget(this);
    infoWidget = new SensorInfoWidget(this);
    chartWidget = new SensorChartWidget(this);

    vertSplit = new QSplitter;
    horSplit = new QSplitter;

    vertSplit->setChildrenCollapsible(false);
    horSplit->setChildrenCollapsible(false);
    horSplit->setOrientation(Qt::Vertical);
    vertSplit->addWidget(horSplit);
    horSplit->addWidget(chartWidget);
    horSplit->addWidget(infoWidget);
    vertSplit->addWidget(listWidget);
    vertSplit->setHandleWidth(0);
    horSplit->setHandleWidth(10);

    QList<int> sz;
    sz << 330 << 100;
    horSplit->setSizes(sz);
    this->setCentralWidget(vertSplit);

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoad);

    connect(listWidget, &SensorListWidget::nameCpy, this, &MainWindow::printInfo);
    connect(listWidget, &SensorListWidget::tryNew, this, &MainWindow::onTryNew);
    connect(listWidget, &SensorListWidget::removedSensor, this, &MainWindow::onRemovedSensor);
    connect(listWidget, &SensorListWidget::clearedList, this, &MainWindow::onClearedList);
    connect(listWidget, &SensorListWidget::curSensorChange, this, &MainWindow::onCurChange);

    connect(infoWidget, &SensorInfoWidget::editSensor, this, &MainWindow::onEditSensor);
    connect(infoWidget, &SensorInfoWidget::beginSim, this, &MainWindow::onBeginSim);
    connect(infoWidget, &SensorInfoWidget::clearSensor, this, &MainWindow::onClearSensor);

    connect(horSplit, &QSplitter::splitterMoved, this, [this](int p)
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

GenericSensor *MainWindow::newSensor(const string &name, const string &desc, const string &component, int max, int temp) const
{
    if(component == "CPU")
    {
        return new CPUSensor(name, desc, max, temp);
    }

    if(component == "GPU")
    {
        return new GPUSensor(name, desc, max, temp);
    }

    if(component == "RAM")
    {
        return new RAMSensor(name, desc, max, temp);
    }

    return nullptr;
}

GenericSensor *MainWindow::convertJson(const QJsonObject &jsonSensor) const
{
    GenericSensor *temp = newSensor(
        jsonSensor["name"].toString().toStdString(),
        jsonSensor["description"].toString().toStdString(),
        jsonSensor["component"].toString().toStdString(),
        jsonSensor["max"].toString().toInt(),
        jsonSensor["temperature"].toString().toInt());

    if(!temp)
        return nullptr;

    QJsonArray jsonData = jsonSensor["data"].toArray();
    for(const auto &data : jsonData)
    {
        QJsonObject point = data.toObject();
        int val = point["value"].toInt();
        int timestamp = point["timestamp"].toInt();
        bool bad = point["bad"].toBool();
        temp->insertInfo(val, timestamp, bad);
    }

    return temp;
}

void MainWindow::saveList(const vector<GenericSensor *> &v, const QString &fname) const
{
    QJsonArray jsonList;
    for(auto it = v.begin(); it != v.end(); ++it)
    {
        QJsonObject jsonSensor;
        (*it)->accept(visitor);

        jsonSensor["name"] = QString::fromStdString((*it)->getName());
        jsonSensor["description"] = QString::fromStdString((*it)->getDesc());
        jsonSensor["component"] = QString::fromStdString(visitor->getType());
        jsonSensor["max"] = QString::number((*it)->getMax());
        jsonSensor["temperature"] = QString::number((*it)->getTemp());

        QJsonArray jsonData;
        for(int i = 0; i < (*it)->getCount(); ++i)
        {
            PointInfo val = (*it)->getData(i);
            QJsonObject jsonInfo;
            jsonInfo["value"] = val.getVal();
            jsonInfo["timestamp"] = val.getTime();
            jsonInfo["bad"] = val.isBad();
            jsonData.append(jsonInfo);
        }

        jsonSensor["data"] = jsonData;
        jsonList.append(jsonSensor);
    }

    QJsonDocument json(jsonList);
    QFile file(fname);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(json.toJson(QJsonDocument::Indented));
        file.close();
    }
}

vector<GenericSensor *> MainWindow::loadList(const QString &fname)
{
    QFile file(fname);
    if(!file.open(QIODevice::ReadOnly))
    {
        return {};
    }

    listWidget->fileClearList();

    QByteArray raw = file.readAll();
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(raw);
    QJsonArray jsonList = json.array();
    vector<GenericSensor *> tempList;
    for(const auto &jsonSensor : jsonList)
    {
        GenericSensor *tempSen = convertJson(jsonSensor.toObject());
        if(tempSen)
        {
            tempList.push_back(tempSen);
            listWidget->newButton(tempSen, visitor);
        }
    }

    return tempList;
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
    infoWidget->setComponent(QString::fromStdString(visitor->getType()), QString::fromStdString(visitor->getChartUnit()));
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
    chartWidget->resetChart();
}

void MainWindow::onClearedList()
{
    listWidget->setCurrent(nullptr);
    list->emptyContainer();
    infoWidget->resetFields();
    chartWidget->resetChart();
}

void MainWindow::onBeginSim()
{
    if(listWidget->getCurrent() != nullptr)
    {
        listWidget->getCurrent()->populate();
        chartWidget->showChart(listWidget->getCurrent());

        if(!isSplitterGood)
        {
            QList<int> nsz;
            nsz << 330 << 100;
            horSplit->setSizes(nsz);
        }
    }
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

void MainWindow::onClearSensor()
{
    if(listWidget->getCurrent() != nullptr)
    {
        listWidget->getCurrent()->clearData();
        chartWidget->resetChart();
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
    chartWidget->resetChart();
}

void MainWindow::onCurChange()
{
    if(listWidget->getCurrent() != nullptr)
        chartWidget->showChart(listWidget->getCurrent());
}

void MainWindow::onSave()
{
    QString fName =
        QFileDialog::getSaveFileName(this, tr("Save List"), "",
                                    tr("JSON Files (*.json)"));

    if(fName.isEmpty())
        return;

    saveList(SensorContainer::getContainer(), fName);
    QMessageBox::information(this, tr("Save List"), tr("List saved in file."));
}

void MainWindow::onLoad()
{
    QString fName =
        QFileDialog::getOpenFileName(this, tr("Load List"), "",
                                    tr("JSON Files (*.json)"));

    if(fName.isEmpty())
        return;

    vector<GenericSensor *> sensorList = loadList(fName);
    if(sensorList.empty())
    {
        QMessageBox::warning(this, tr("Load List"), tr("No sensors in file or file could not be parsed."));
        return;
    }

    SensorContainer::copySensors(sensorList);
    chartWidget->resetChart();
    QMessageBox::information(this, tr("Load List"), tr("Sensors loaded from file."));
}
