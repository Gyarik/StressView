#ifndef VISITOR_H
#define VISITOR_H
#include "../visitor/genericvisitor.h"

class Visitor : public GenericVisitor
{
private:
    string type;

public:
    Visitor();
    virtual ~Visitor();
    virtual void visit(const CPUSensor *) override;
    virtual string getType() const override;
};

#endif
