#include "sensorcontainer.h"
#include "../model/genericsensor.h"

vector<GenericSensor *> SensorContainer::m_cont;

void SensorContainer::emptyContainer()
{
    for(auto it = m_cont.begin(); it != m_cont.end(); ++it)
        delete *it;
    m_cont.clear();
}

const vector<GenericSensor *> & SensorContainer::getContainer()
{
    return m_cont;
}

bool SensorContainer::addSensor(GenericSensor *sen)
{

    for(auto it = m_cont.begin(); it != m_cont.end(); ++it)
    {
        if((*it)->getName() == sen->getName())
            return false;
    }

    m_cont.push_back(sen);
    return true;
}

void SensorContainer::removeSensor(GenericSensor *sen)
{
    for(auto it = m_cont.begin(); it != m_cont.end(); ++it)
    {
        if((*it)->getName() == sen->getName())
        {
            m_cont.erase(it);
            return;
        }
    }
}

void SensorContainer::editSensor(GenericSensor *sen, const string &name, const string &desc, int max, int temp)
{
    for(auto it = m_cont.begin(); it != m_cont.end(); ++it)
    {
        if((*it)->getName() == sen->getName())
        {
            (*it)->setName(name);
            (*it)->setDesc(desc);
            (*it)->setMax(max);
            (*it)->setTemp(temp);
        }
    }
}

GenericSensor * SensorContainer::searchSensor(const string &name) const
{
    for(auto it = m_cont.begin(); it != m_cont.end(); ++it)
    {
        if((*it)->getName() == name)
            return *it;
    }
    return nullptr;
}
