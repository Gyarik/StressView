#include "sensorinfowidget.h"
#include "ui_sensorinfowidget.h"

SensorInfoWidget::SensorInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::SensorInfoWidget)
{
    ui->setupUi(this);
    ui->frame->setFrameStyle(QFrame::Box);
    ui->NameField->setStyleSheet("QTextEdit { background: transparent; }");
    ui->NameField->setAttribute(Qt::WA_TranslucentBackground);
    ui->TypeField->setStyleSheet("QTextEdit { background: transparent; }");
    ui->TypeField->setAttribute(Qt::WA_TranslucentBackground);
    ui->DescField->setStyleSheet("QTextEdit { background: transparent; }");
    ui->DescField->setAttribute(Qt::WA_TranslucentBackground);
    ui->MaxField->setStyleSheet("QTextEdit { background: transparent; }");
    ui->MaxField->setAttribute(Qt::WA_TranslucentBackground);
    ui->TempField->setStyleSheet("QTextEdit { background: transparent; }");
    ui->TempField->setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->SimButton, &QPushButton::clicked, this, [this]() { emit beginSim(); });
    connect(ui->ClearButton, &QPushButton::clicked, this, [this]() { emit clearSensor(); });
    connect(ui->EditButton, &QPushButton::clicked, this, [this]() { emit editSensor(); });
}

SensorInfoWidget::~SensorInfoWidget()
{
    delete ui;
}

void SensorInfoWidget::setName(const QString &name)
{
    ui->NameField->setText(name);
}

void SensorInfoWidget::setDesc(const QString &desc)
{
    ui->DescField->setText(desc);
}

void SensorInfoWidget::setComponent(const QString &comp, const QString &unit)
{
    ui->TypeField->setText(comp);
    ui->TypeUnit->setText(unit);
}

void SensorInfoWidget::setBounds(const QString &max, const QString &temp)
{
    ui->MaxField->setText(max);
    ui->TempField->setText(temp);
}

void SensorInfoWidget::resetFields()
{
    ui->NameField->clear();
    ui->DescField->clear();
    ui->TypeField->clear();
    ui->MaxField->clear();
    ui->TempField->clear();
    ui->TypeUnit->clear();
}
