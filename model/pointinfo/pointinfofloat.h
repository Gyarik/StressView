#ifndef POINTINFOFLOAT_H
#define POINTINFOFLOAT_H
#include "../../model/pointinfo/pointinfo.h"

class PointInfoFloat : public PointInfo
{
private:
    float m_val;

public:
    PointInfoFloat(float = 0.0f, int = 0, int = 40, bool = false);
    virtual ~PointInfoFloat();
    float getVal() const;
};

#endif
