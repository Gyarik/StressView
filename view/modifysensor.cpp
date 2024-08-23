#include "modifysensor.h"
#include "ui_modifysensor.h"

ModifySensor::ModifySensor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifySensor)
{
    ui->setupUi(this);
}

ModifySensor::~ModifySensor()
{
    delete ui;
}
