#include "addsensor.h"
#include "ui_addsensor.h"

AddSensor::AddSensor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddSensor)
{
    ui->setupUi(this);
}

AddSensor::~AddSensor()
{
    delete ui;
}
