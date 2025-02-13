#ifndef GENERICSENSOR_H
#define GENERICSENSOR_H
#include "../model/pointinfo/pointinfo.h"
#include <string>
#include <vector>
#include <variant>

using std::string;
using std::vector;
using std::variant;

class GenericVisitor;

class GenericSensor
{
private:
    string m_name, m_desc;
    int m_max, m_temp;

protected:
    vector<PointInfo> m_data;

public:
    GenericSensor(const string & = "untitled", const string & = "", int = 50, int = 80);
    virtual ~GenericSensor() = 0;
    virtual void populate() = 0;
    string getName() const;
    string getDesc() const;
    int getMax() const;
    int getTemp() const;
    int getCount() const;
    PointInfo getData(int) const;
    void setName(const string &);
    void setDesc(const string &);
    void setMax(int);
    void setTemp(int);
    void clearData();
    void insertInfo(int, int, bool);

    virtual void accept(GenericVisitor *) const = 0;
    virtual void setupButton(GenericVisitor *) const = 0;
    virtual void setChartUnit(GenericVisitor *) const = 0;
};

#endif
