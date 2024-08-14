#include "pointinfoint.h"

PointInfoInt::PointInfoInt(int val, int time, int temp, bool bad)
    : PointInfo::PointInfo(time, temp, bad), m_val(val) {}

PointInfoInt::~PointInfoInt() {}

int PointInfoInt::getVal() const
{
    return m_val;
}
