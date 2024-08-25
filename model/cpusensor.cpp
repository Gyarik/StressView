#include "cpusensor.h"
#include "../visitor/genericvisitor.h"

CPUSensor::CPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

CPUSensor::~CPUSensor() {}

void CPUSensor::populate()
{

    // Delete all data before creating new simulation
    m_data.clear();

    // Declare variables and create first arbitrary value
    const int maxVal = getMax();
    const int maxTemp = getTemp();
    int curVal = maxVal - (int)(maxVal * 0.1f);
    const int firstVal = curVal;
    int curTemp = maxTemp - (int)(maxTemp * 0.2f);
    m_data.push_back(PointInfo(firstVal, 0, curTemp, false));
    bool bad = false;
    int randMinTemp = curTemp - (int)(0.1f * curTemp);
    int randMin = 0;
    int randMax = 100;

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        // curTemp - (int)(0.1f * curTemp), maxTemp
        curTemp = rand() % (maxTemp - randMinTemp + 1) + randMinTemp;

        // If temperature is over 95C, 70% chance to generate bad number
        if(curTemp >= 95 && rand() % 100 + 1 <= 70)
        {
            // 0.5f * firstVal, 0.7f * firstVal
            randMin = (int)(0.5f * firstVal);
            randMax = (int)(0.7f * firstVal);
            curVal = firstVal - rand() % (randMax - randMin + 1) + randMin;
        }
        // otherwise generate normally
        else
        {
            randMin = firstVal - (int)(0.1f * firstVal);
            curVal = rand() % (maxVal - randMin + 1) + randMin;
        }

        // A performance value is bad when current value is 20% worse than first value
        bad = curVal <= (int)(0.8f * firstVal);

        m_data.push_back(PointInfo(curVal, i+1, curTemp, bad));
    }
}

void CPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}

void CPUSensor::setupButton(GenericVisitor *visitor) const
{
    return visitor->listButton(this);
}

void CPUSensor::setChartUnit(GenericVisitor *visitor) const
{
    return visitor->setChartUnit(this);
}
