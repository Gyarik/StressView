#include "addsensor.h"
#include "ui_addsensor.h"

AddSensor::AddSensor(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddSensor)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString("Create new sensor"));
    ui->NameInput->setFocus();

    QRegularExpression regexpName("[\\p{L}0-9]*");
    QRegularExpressionValidator *validName = new QRegularExpressionValidator(regexpName);
    ui->NameInput->setValidator(validName);
    ui->NameInput->setMaxLength(32);

    QRegularExpression regexpMax("^[0-9]*$");
    QRegularExpressionValidator *validMax = new QRegularExpressionValidator(regexpMax);
    ui->MaxInput->setValidator(validMax);
    ui->MaxInput->setMaxLength(8);

    ui->TempInput->setValidator(validMax);
    ui->TempInput->setMaxLength(3);
}

AddSensor::~AddSensor()
{
    delete ui;
}

void AddSensor::on_CPUButton_toggled(bool checked)
{
    if(checked)
    {
        ui->MaxInput->setPlaceholderText("4200");
        ui->TempInput->setPlaceholderText("100");
        ui->UnitLabel->setText("MHz");
        ui->MaxInput->setMaxLength(5);
    }
}

void AddSensor::on_GPUButton_toggled(bool checked)
{
    if(checked)
    {
        ui->MaxInput->setPlaceholderText("2400");
        ui->TempInput->setPlaceholderText("120");
        ui->UnitLabel->setText("MHz");
        ui->MaxInput->setMaxLength(4);
    }
}

void AddSensor::on_RAMButton_toggled(bool checked)
{
    if(checked)
    {
        ui->MaxInput->setPlaceholderText("16");
        ui->TempInput->setPlaceholderText("75");
        ui->UnitLabel->setText("GiB");
        ui->MaxInput->setMaxLength(4);
    }
}

void AddSensor::on_NewSensorButton_clicked()
{
    QString name = ui->NameInput->text().trimmed();
    QString max = ui->MaxInput->text().trimmed();
    QString temp = ui->TempInput->text().trimmed();

    if(name.isEmpty())
    {
        return;
    }
    else
    {
        if((max.isEmpty() && temp.isEmpty()) || (!max.isEmpty() && !temp.isEmpty()))
        {
            if(max.isEmpty())
                max = ui->MaxInput->placeholderText();

            if(temp.isEmpty())
                temp = ui->TempInput->placeholderText();

            if(ui->CPUButton->isChecked())
            {
                CPUSensor *createdSensor =
                    new CPUSensor(ui->NameInput->text().toStdString(), ui->DescInput->text().toStdString(), max.toInt(), temp.toInt());
                emit infoExists(createdSensor);
            }

            if(ui->GPUButton->isChecked())
            {
                GPUSensor *createdSensor =
                    new GPUSensor(ui->NameInput->text().toStdString(), ui->DescInput->text().toStdString(), max.toInt(), temp.toInt());
                emit infoExists(createdSensor);
            }

            if(ui->RAMButton->isChecked())
            {
                RAMSensor *createdSensor =
                    new RAMSensor(ui->NameInput->text().toStdString(), ui->DescInput->text().toStdString(), max.toInt() * 1024, temp.toInt());
                emit infoExists(createdSensor);
            }
        }
        else
        {
            return;
        }
    }
}

