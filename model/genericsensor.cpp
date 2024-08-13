#include "genericsensor.h"

GenericSensor::GenericSensor(const string &name, const string &desc, int max, int temp)
    : m_name(name), m_desc(desc), m_max(max), m_temp(temp) {}

string GenericSensor::getName() const
{
    return m_name;
}

string GenericSensor::getDesc() const
{
    return m_desc;
}

int GenericSensor::getMax() const
{
    return m_max;
}

int GenericSensor::getTemp() const
{
    return m_temp;
}

int GenericSensor::getCount() const
{
    return m_data.size();
}
