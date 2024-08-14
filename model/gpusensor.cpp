#include "gpusensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/pointinfo/pointinfoint.h"

GPUSensor::GPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

GPUSensor::~GPUSensor() {}

void GPUSensor::populate()
{
    // Delete all data before creating new simulation
    this->deleteData();

    // Declare variables and create first value
    const int maxVal = getMax();
    const int maxTemp = getTemp();
    int randMinInt = maxVal - (int)(0.6f * maxVal);
    int randMaxInt = 5000;
    int curVal = rand() % (maxVal - randMinInt + 1) + randMinInt;
    // const int firstVal = curVal;
    randMinInt = (int)(0.5f * maxTemp);
    int curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;
    int prevVal = curVal;
    int firstVal = curVal;
    bool bad = false;

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        randMinInt = curTemp - (int)(0.1f * curTemp);
        curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;

        // If previously bad and temperature is still too high, keep similar value
        if(bad && curTemp >= 100)
        {
            randMinInt = prevVal - (int)(0.05f * prevVal);
            randMaxInt = prevVal + (int)(0.05f * prevVal);
        }
        // If temperature is over 100C, 80% chance to generate bad number
        else if(curTemp >= 100 && rand() % 100 + 1 <= 80)
        {
            randMinInt = (int)(0.3f * firstVal);
            randMaxInt = (int)(0.6f * firstVal);
        }
        // otherwise generate normally
        else
        {
            randMinInt = prevVal - (int)(0.1f * prevVal);
            randMaxInt = maxVal;
        }
        curVal = rand() % (randMaxInt - randMinInt + 1) + randMinInt;

        bad = curVal <= (0.5f * firstVal);

        m_data.push_back(new PointInfoInt(curVal, i+1, curTemp, bad));
    }
}

void GPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}
