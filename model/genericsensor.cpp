#include "genericsensor.h"

GenericSensor::GenericSensor(const string &name, const string &desc, int max, int temp)
    : m_name(name), m_desc(desc), m_max(max), m_temp(temp) {}

GenericSensor::~GenericSensor()
{
    this->deleteData();
}

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

void GenericSensor::setName(const string &name)
{
    this->m_name = name;
}

void GenericSensor::setDesc(const string &name)
{
    this->m_desc = desc;
}

void GenericSensor::setMax(int max)
{
    this->m_max = max;
}

void GenericSensor::setTemp(int temp)
{
    this->m_temp = temp;
}

void GenericSensor::deleteData()
{
    for(auto it = m_data.begin(); it != m_data.end(); ++it)
        delete *it;
    m_data.clear();
}
