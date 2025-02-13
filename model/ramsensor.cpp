#include "ramsensor.h"
#include "../visitor/genericvisitor.h"

RAMSensor::RAMSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

RAMSensor::~RAMSensor() {}

void RAMSensor::populate()
{
    // Delete all data before creating new simulation
    m_data.clear();

    // Declare variables and create first value
    const int maxVal = getMax();
    const int maxTemp = getTemp();
    int randMinInt = (int)(0.01f * maxVal);
    int randMaxInt = (int)(0.03f * maxVal);
    int curVal = rand() % (randMaxInt - randMinInt + 1) + randMinInt;
    randMinInt = (int)(0.5f * maxTemp);
    randMaxInt = maxTemp - (int)(0.7f * maxTemp);
    int curTemp = rand() % (randMaxInt - randMinInt + 1) + randMinInt;
    int firstVal = curVal;
    bool bad = false;
    m_data.push_back(PointInfo(firstVal, 0, curTemp, bad));

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        randMinInt = curTemp - (int)(0.1f * curTemp);
        curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;

        // If temperature is over 75C, 40% chance to (almost) fill RAM
        if(curTemp >= 75 && rand() % 100 + 1 <= 40)
        {
            randMinInt = (int)(0.95f * maxVal);
            randMaxInt = maxVal;
        }
        // otherwise generate normally
        else
        {
            int scale = (int)(((float)curTemp / (float) maxTemp) * firstVal);
            randMinInt = firstVal - scale;
            scale = (int)(((float)curTemp / (float) maxTemp) * maxVal);
            randMaxInt = maxVal - scale;
        }
        curVal = rand() % (randMaxInt - randMinInt + 1) + randMinInt;

        bad = curVal >= (0.95f * maxVal);

        m_data.push_back(PointInfo(curVal, i+1, curTemp, bad));
    }
}

void RAMSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}

void RAMSensor::setupButton(GenericVisitor *visitor) const
{
    return visitor->listButton(this);
}

void RAMSensor::setChartUnit(GenericVisitor *visitor) const
{
    return visitor->setChartUnit(this);
}
