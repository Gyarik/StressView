#include "modifysensor.h"
#include "ui_modifysensor.h"

ModifySensor::ModifySensor(GenericSensor *sen, QWidget *parent)
    : QDialog(parent), ui(new Ui::ModifySensor), sensor(sen)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Edit Sensor"));

    ui->NameInput->setText(QString::fromStdString(sensor->getName()));
    ui->DescInput->setText(QString::fromStdString(sensor->getDesc()));
    ui->MaxInput->setText(QString::number(sensor->getMax()));
    ui->TempInput->setText(QString::number(sensor->getTemp()));
    QRegularExpression regex("[a-zA-Z0-9]*");
    QRegularExpressionValidator *valid = new QRegularExpressionValidator(regex);
    ui->NameInput->setValidator(valid);
    ui->NameInput->setMaxLength(32);
    QRegularExpression regexnum("[0-9]*");
    QRegularExpressionValidator *validnum = new QRegularExpressionValidator(regexnum);
    ui->MaxInput->setValidator(validnum);
    ui->TempInput->setValidator(validnum);
    ui->MaxInput->setMaxLength(5);
    ui->TempInput->setMaxLength(3);
}

ModifySensor::~ModifySensor()
{
    delete ui;
}

string ModifySensor::getName()
{
    return ui->NameInput->text().trimmed().toStdString();
}

// Slots

void ModifySensor::on_CancelButton_clicked()
{
    close();
}

void ModifySensor::on_ConfirmButton_clicked()
{
    if(ui->NameInput->text().trimmed().isEmpty())
    {
        ErrorWindow *Error = new ErrorWindow("Name cannot be empty");
        Error->show();
    }
    else
        emit changeSensor();
}

void ModifySensor::onCanEdit()
{
    string prev = sensor->getName();
    sensor->setName(QString(ui->NameInput->text()).toStdString());
    sensor->setDesc(QString(ui->DescInput->text()).toStdString());
    sensor->setMax(QString(ui->MaxInput->text()).toInt());
    sensor->setTemp(QString(ui->TempInput->text()).toInt());
    emit refreshInfo(sensor, prev);
    close();
}
