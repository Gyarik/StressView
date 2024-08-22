#include "cpusensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/pointinfo/pointinfofloat.h"

CPUSensor::CPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

CPUSensor::~CPUSensor() {}

void CPUSensor::populate()
{

    // Delete all data before creating new simulation
    this->deleteData();

    // Declare variables and create first arbitrary value
    const float maxVal = getMax() / 1000.0f;
    const int maxTemp = getTemp();
    float curVal = maxVal - maxVal * 0.1f;
    const float firstVal = curVal;
    int curTemp = maxTemp - (int)(maxTemp * 0.2f);
    m_data.push_back(new PointInfoFloat(firstVal, 0, curTemp, false));
    bool bad = false;
    int randMinInt = curTemp - (int)(0.1f * curTemp);
    float randMinFloat = 0.0f;
    float randMaxFloat = 100.0f;

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        // curTemp - (int)(0.1f * curTemp), maxTemp
        curTemp = rand() % (maxTemp - randMinInt + 1) + randMinInt;

        // If temperature is over 95C, 70% chance to generate bad number
        if(curTemp >= 95 && rand() % 100 + 1 <= 70)
        {
            // 0.5f * firstVal, 0.7f * firstVal
            randMinFloat = 0.5f * firstVal;
            randMaxFloat = 0.7f * firstVal;
            curVal = firstVal - (randMinFloat + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/(randMaxFloat-randMinFloat))));
        }
        // otherwise generate normally
        else
        {
            randMinFloat = firstVal - 0.1f * firstVal;
            curVal = randMinFloat + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/(maxVal-randMinFloat)));
        }

        // A performance value is bad when current value is 20% worse than first value
        bad = curVal <= (0.8f * firstVal);

        m_data.push_back(new PointInfoFloat(curVal, i+1, curTemp, bad));
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
