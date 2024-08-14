#include "cpusensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/pointinfo/pointinfofloat.h"
#include <random>

CPUSensor::CPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

CPUSensor::~CPUSensor() {}

void CPUSensor::populate()
{
    // Declare variables and create first arbitrary value
    const float maxVal = getMax() / 1000.0f;
    const int maxTemp = getTemp();
    float curVal = maxVal - maxVal * 0.1f;
    float firstVal = curVal;
    int curTemp = maxTemp - (int)(maxTemp * 0.2f);
    m_data.push_back(new PointInfoFloat(firstVal, 0, curTemp, false));
    bool bad = false;

    // Setup random number generation (uniform distribution)
    std::random_device rd;
    std::default_random_engine rng(rd());

    for(int i = 0; i < 20; ++i)
    {
        // Generate temperature
        std::uniform_int_distribution<int> uni(curTemp - (int)(0.1f * curTemp), maxTemp);
        curTemp = uni(rng);

        // If temperature is over 95C, 70% chance to generate bad number
        uni = std::uniform_int_distribution<int>(1, 100);
        std::uniform_real_distribution<float> unifloat(firstVal - 0.1f * firstVal, maxVal);
        if(curTemp >= 95 && uni(rng) <= 70)
        {
            unifloat = std::uniform_real_distribution<float>(0.5f * firstVal, 0.7f * firstVal);
            curVal = firstVal - unifloat(rng);
        }
        // otherwise generate normally
        else
            curVal = unifloat(rng);

        // A performance value is bad when current value is 20% worse than first value
        bad = curVal <= (0.8f * firstVal);

        m_data.push_back(new PointInfoFloat(curVal, i+1, curTemp, bad));
    }
}

void CPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}
