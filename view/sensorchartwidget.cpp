#include "sensorchartwidget.h"
#include "ui_sensorchartwidget.h"

SensorChartWidget::SensorChartWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SensorChartWidget)
{
    ui->setupUi(this);
}

SensorChartWidget::~SensorChartWidget()
{
    delete ui;
}
