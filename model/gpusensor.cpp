#include "gpusensor.h"
#include "../visitor/genericvisitor.h"

GPUSensor::GPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

GPUSensor::~GPUSensor() {}

void GPUSensor::populate() {}

void GPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}
