#ifndef GPUSENSOR_H
#define GPUSENSOR_H
#include "../model/genericsensor.h"

class GPUSensor : public GenericSensor
{
public:
    GPUSensor(const string & = "untitled", const string & = "", int = 200, int = 80);
    virtual ~GPUSensor();
    virtual void populate() override;

    virtual void accept(GenericVisitor *) const override;
    virtual void setupButton(GenericVisitor *) const override;
    virtual void setChartUnit(GenericVisitor *) const override;
};

#endif
