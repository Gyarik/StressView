#include "visitor.h"

Visitor::Visitor() {}

Visitor::~Visitor() {}

void Visitor::visit(const CPUSensor *sensor)
{
    this->type = "CPU";
}

string Visitor::getType() const
{
    return this->type;
}
