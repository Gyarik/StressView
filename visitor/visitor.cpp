#include "visitor.h"

Visitor::Visitor() {}

Visitor::~Visitor() {}

void Visitor::visit(const CPUSensor *sensor)
{
    this->m_type = "CPU";
}

void Visitor::visit(const GPUSensor *sensor)
{
    this->m_type = "GPU";
}

void Visitor::visit(const RAMSensor *sensor)
{
    this->m_type = "RAM";
}

string Visitor::getType() const
{
    return this->m_type;
}

QPushButton *Visitor::getButton() const
{
    return this->m_btn;
}

void Visitor::listButton(const CPUSensor *sensor)
{
    QPushButton *btn = new QPushButton();
    btn->setObjectName(QString::fromStdString(sensor->getName()));
    btn->setFixedSize(QSize(225, 40));
    btn->setStyleSheet("text-align:left;");
    btn->setLayout(new QGridLayout);

    QLabel *txt = new QLabel(QString::fromStdString(sensor->getName()));
    txt->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    btn->layout()->addWidget(txt);
    this->m_btn = btn;
}

void Visitor::listButton(const GPUSensor *sensor)
{
    QPushButton *btn = new QPushButton();
    btn->setObjectName(QString::fromStdString(sensor->getName()));
    btn->setFixedSize(QSize(225, 40));
    btn->setStyleSheet("text-align:left;");
    btn->setLayout(new QGridLayout);

    QLabel *txt = new QLabel(QString::fromStdString(sensor->getName()));
    txt->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    btn->layout()->addWidget(txt);
    this->m_btn = btn;
}

void Visitor::listButton(const RAMSensor *sensor)
{
    QPushButton *btn = new QPushButton();
    btn->setObjectName(QString::fromStdString(sensor->getName()));
    btn->setFixedSize(QSize(225, 40));
    btn->setStyleSheet("text-align:left;");
    btn->setLayout(new QGridLayout);

    QLabel *txt = new QLabel(QString::fromStdString(sensor->getName()));
    txt->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    btn->layout()->addWidget(txt);
    this->m_btn = btn;
}
