#include "cpusensor.h"

CPUSensor::CPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

CPUSensor::~CPUSensor() {}

void CPUSensor::populate()
{

}
