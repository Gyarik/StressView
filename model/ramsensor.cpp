#include "ramsensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/pointinfo/pointinfofloat.h"

RAMSensor::RAMSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

RAMSensor::~RAMSensor() {}

void RAMSensor::populate() {}

void RAMSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}
