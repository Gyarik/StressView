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

string Visitor::getType() const
{
    return this->type;
}
