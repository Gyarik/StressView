#include "gpusensor.h"
#include "../visitor/genericvisitor.h"

GPUSensor::GPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

GPUSensor::~GPUSensor() {}

void GPUSensor::populate()
{
    // Delete all data before creating new simulation
    m_data.clear();

    // Declare variables and create first value
    const int maxVal = getMax();
    const int maxTemp = getTemp();
    int randMinInt = maxVal - (int)(0.6f * maxVal);
    int randMaxInt = 5000;
    int curVal = rand() % (maxVal - randMinInt + 1) + randMinInt;
    // const int firstVal = curVal;
    randMinInt = (int)(0.5f * maxTemp);
    int curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;
    int prevTemp = curTemp;
    int prevVal = curVal;
    int firstVal = curVal;
    bool bad = false;
    m_data.push_back(PointInfo(firstVal, 0, curTemp, bad));

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        randMinInt = curTemp - (int)(0.1f * curTemp);
        curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;

        // If previously bad and temperature is still too high, keep similar value and temp
        if(bad && curTemp >= 100)
        {
            randMinInt = prevVal - (int)(0.01f * prevVal);
            randMaxInt = prevVal + (int)(0.01f * prevVal);
            curTemp = rand() % (maxTemp - (int)(0.95f * prevTemp) + 1) + (int)(0.95f * prevTemp);
        }
        // If temperature is over 100C, 80% chance to generate bad number
        else if(curTemp >= 100 && rand() % 100 + 1 <= 80)
        {
            randMinInt = (int)(0.3f * firstVal);
            randMaxInt = (int)(0.5f * firstVal);
        }
        // otherwise generate normally
        else
        {
            randMinInt = prevVal - (int)(0.01f * prevVal);
            randMaxInt = maxVal;
        }
        curVal = rand() % (randMaxInt - randMinInt + 1) + randMinInt;

        bad = curVal <= (int)(0.5f * firstVal);

        m_data.push_back(PointInfo(curVal, i+1, curTemp, bad));
    }
}

void GPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}

void GPUSensor::setupButton(GenericVisitor *visitor) const
{
    return visitor->listButton(this);
}

void GPUSensor::setChartUnit(GenericVisitor *visitor) const
{
    return visitor->setChartUnit(this);
}
