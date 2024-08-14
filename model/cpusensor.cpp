#include "cpusensor.h"
#include "../visitor/genericvisitor.h"
#include "../model/pointinfo/pointinfofloat.h"
#include <random>

CPUSensor::CPUSensor(const string &name, const string &desc, int max, int temp)
    : GenericSensor::GenericSensor(name, desc, max, temp) {}

CPUSensor::~CPUSensor() {}

void CPUSensor::populate()
{
    const float maxVal = getMax() / 1000.0f;
    const int maxTemp = getTemp();
    float curVal;
    float firstVal = curVal = maxVal - maxVal * 0.1f;
    int curTemp = maxTemp - (int)(maxTemp * 0.2f);
    m_data.push_back(new PointInfoFloat(firstVal, 0, curTemp, false));
    float prevVal = curVal;
    bool bad = false;

    std::random_device rd;
    std::default_random_engine rng(rd());

    for(int i = 0; i < 20; ++i)
    {
        std::uniform_int_distribution<int> uni(curTemp - (int)(0.1f * curTemp), maxTemp);
        curTemp = uni(rng);

        uni = std::uniform_int_distribution<int>(0, 100);
        if(curTemp >= 95 && uni(rng) <= 70)
        {
            std::uniform_real_distribution<float> unifloat(0.5f * prevVal, 0.7f * prevVal);
            curVal = prevVal - unifloat(rng);
        }
        else
        {
            std::uniform_real_distribution<float> unifloat(firstVal - 0.1f * firstVal, maxVal);
            curVal = unifloat(rng);
        }

        bad = curVal <= (0.8f * firstVal);

        m_data.push_back(new PointInfoFloat(curVal, i+1, curTemp, bad));
        prevVal = curVal;
    }
}

void CPUSensor::accept(GenericVisitor *visitor) const
{
    return visitor->visit(this);
}
