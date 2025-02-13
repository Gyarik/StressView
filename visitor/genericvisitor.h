#ifndef GENERICVISITOR_H
#define GENERICVISITOR_H
#include "../model/cpusensor.h"
#include "../model/gpusensor.h"
#include "../model/ramsensor.h"
#include <string>
#include <QPushButton>

using std::string;

class GenericVisitor
{
public:
    GenericVisitor();
    virtual ~GenericVisitor();
    virtual void visit(const CPUSensor *) = 0;
    virtual void visit(const GPUSensor *) = 0;
    virtual void visit(const RAMSensor *) = 0;

    virtual string getType() const = 0;
    virtual QPushButton *getButton() const = 0;
    virtual string getChartUnit() const = 0;

    virtual void listButton(const CPUSensor *) = 0;
    virtual void listButton(const GPUSensor *) = 0;
    virtual void listButton(const RAMSensor *) = 0;

    virtual void setChartUnit(const CPUSensor *) = 0;
    virtual void setChartUnit(const GPUSensor *) = 0;
    virtual void setChartUnit(const RAMSensor *) = 0;
};

#endif
