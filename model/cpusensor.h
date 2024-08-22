#ifndef CPUSENSOR_H
#define CPUSENSOR_H
#include "../model/genericsensor.h"

class CPUSensor : public GenericSensor
{
public:
    CPUSensor(const string & = "untitled", const string & = "", int = 0, int = 80);
    virtual ~CPUSensor();
    virtual void populate() override;

    virtual void accept(GenericVisitor *) const override;
    virtual void setupButton(GenericVisitor *) const override;
};

#endif
