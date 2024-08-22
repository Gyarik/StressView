#include "sensorlistwidget.h"
#include "ui_sensorlistwidget.h"

SensorListWidget::SensorListWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SensorListWidget)
{
    ui->setupUi(this);
}

SensorListWidget::~SensorListWidget()
{
    delete ui;
}
