#ifndef GENERICSENSOR_H
#define GENERICSENSOR_H
#include "../model/pointinfo.h"
#include <string>
#include <vector>
#include <variant>

using std::string;
using std::vector;
using std::variant;

class GenericSensor
{
private:
    string m_name, m_desc;
    int m_max, m_temp;

protected:
    vector<variant<PointInfo<int>, PointInfo<float>>> m_data;

public:
    GenericSensor(const string & = "untitled", const string & = "", int = 0, int = 80);
    virtual ~GenericSensor() = 0;
    virtual void populate() = 0;
    string getName() const;
    string getDesc() const;
    int getMax() const;
    int getTemp() const;
    int getCount() const;
};

#endif
