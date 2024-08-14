#ifndef POINTINFOINT_H
#define POINTINFOINT_H
#include "../../model/pointinfo/pointinfo.h"

class PointInfoInt : public PointInfo
{
private:
    int m_val;

public:
    PointInfoInt(int = 0, int = 0, int = 40, bool = false);
    virtual ~PointInfoInt();
    int getVal() const;
};

#endif
