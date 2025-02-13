#ifndef RAMSENSOR_H
#define RAMSENSOR_H
#include "../model/genericsensor.h"

class RAMSensor : public GenericSensor
{
public:
    RAMSensor(const string & = "untitled", const string & = "", int = 1, int = 80);
    virtual ~RAMSensor();
    virtual void populate() override;

    virtual void accept(GenericVisitor *) const override;
    virtual void setupButton(GenericVisitor *) const override;
    virtual void setChartUnit(GenericVisitor *) const override;
};

#endif
