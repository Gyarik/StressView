#ifndef VISITOR_H
#define VISITOR_H
#include "../visitor/genericvisitor.h"
#include <QLabel>
#include <QBoxLayout>

class Visitor : public GenericVisitor
{
private:
    string m_type;
    QPushButton *m_btn;
    string m_unit;

public:
    Visitor();
    virtual ~Visitor();
    virtual void visit(const CPUSensor *) override;
    virtual void visit(const GPUSensor *) override;
    virtual void visit(const RAMSensor *) override;

    virtual string getType() const override;
    virtual QPushButton *getButton() const override;
    virtual string getChartUnit() const override;

    virtual void listButton(const CPUSensor *) override;
    virtual void listButton(const GPUSensor *) override;
    virtual void listButton(const RAMSensor *) override;

    virtual void setChartUnit(const CPUSensor *) override;
    virtual void setChartUnit(const GPUSensor *) override;
    virtual void setChartUnit(const RAMSensor *) override;
};

#endif
