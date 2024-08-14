#ifndef GENERICVISITOR_H
#define GENERICVISITOR_H
#include "../model/cpusensor.h"
#include "../model/gpusensor.h"
#include "../model/ramsensor.h"
#include <string>

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
};

#endif
