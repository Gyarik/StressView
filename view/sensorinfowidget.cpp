#include "sensorinfowidget.h"
#include "ui_sensorinfowidget.h"

SensorInfoWidget::SensorInfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SensorInfoWidget)
{
    ui->setupUi(this);
}

SensorInfoWidget::~SensorInfoWidget()
{
    delete ui;
}
