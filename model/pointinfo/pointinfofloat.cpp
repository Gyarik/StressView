#include "pointinfofloat.h"

PointInfoFloat::PointInfoFloat(float val, int time, int temp, bool bad)
    : PointInfo::PointInfo(time, temp, bad), m_val(val) {}

PointInfoFloat::~PointInfoFloat() {}

float PointInfoFloat::getVal() const
{
    return m_val;
}
