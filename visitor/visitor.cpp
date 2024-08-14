#include "visitor.h"

Visitor::Visitor() {}

Visitor::~Visitor() {}

void Visitor::visit(const CPUSensor *sensor)
{
    this->type = "CPU";
}

void Visitor::visit(const GPUSensor *sensor)
{
    this->type = "GPU";
}

void Visitor::visit(const RAMSensor *sensor)
{
    this->type = "RAM";
}

string Visitor::getType() const
{
    return this->type;
}
