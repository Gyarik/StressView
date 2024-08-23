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

void AddSensor::setRanges(int min, int max, int tempmin, int tempmax)
{
    r_min = min;
    r_max = max;
    r_tempmin = tempmin;
    r_tempmax = tempmax;
    s_maxrange =
        "[" + QString::number(r_min) + "-" + QString::number(r_max) + "] " + ui->UnitLabel->text().trimmed();
    s_temprange =
        "[" + QString::number(r_tempmin) + "-" + QString::number(r_tempmax) + "] °C";
}

bool AddSensor::isInRange() const
{
    int maxtest = (ui->MaxInput->text().isEmpty()) ?
                      (ui->MaxInput->placeholderText().toInt()) : (ui->MaxInput->text().toInt());
    int temptest = (ui->TempInput->text().isEmpty()) ?
                       (ui->TempInput->placeholderText().toInt()) : (ui->TempInput->text().toInt());
    if(maxtest > r_max || maxtest < r_min || temptest > r_tempmax || temptest < r_tempmin)
        return false;
    return true;
}

// Slots

void AddSensor::on_CPUButton_toggled(bool checked)
{
    if(checked)
    {
        ui->MaxInput->setPlaceholderText("4200");
        ui->TempInput->setPlaceholderText("100");
        ui->UnitLabel->setText("MHz");
        setRanges(500, 10000, 30, 150);
        ui->MaxRangeLabel->setText(s_maxrange);
        ui->TempRangeLabel->setText(s_temprange);
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
        setRanges(200, 5000, 30, 180);
        ui->MaxRangeLabel->setText(s_maxrange);
        ui->TempRangeLabel->setText(s_temprange);
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
        setRanges(1, 512, 30, 120);
        ui->MaxRangeLabel->setText(s_maxrange);
        ui->TempRangeLabel->setText(s_temprange);
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
        ErrorWindow *Error = new ErrorWindow("Sensor name cannot be empty", this);
        Error->show();
    }
    else if(!ui->CPUButton->isChecked() && !ui->GPUButton->isChecked() && !ui->RAMButton->isChecked())
    {
        ErrorWindow *Error = new ErrorWindow("Sensor type not selected", this);
        Error->show();
    }
    else
    {
        if((max.isEmpty() && temp.isEmpty()) || (!max.isEmpty() && !temp.isEmpty()))
        {
            if(max.isEmpty())
                max = ui->MaxInput->placeholderText();

            if(temp.isEmpty())
                temp = ui->TempInput->placeholderText();

            if(!isInRange())
            {
                ErrorWindow *Error = new ErrorWindow("One or more values are out of bounds", this);
                Error->show();
                return;
            }

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

            close();
        }
        else
        {
            ErrorWindow *Error = new ErrorWindow("Bounds info is missing", this);
            Error->show();
        }
    }
}

