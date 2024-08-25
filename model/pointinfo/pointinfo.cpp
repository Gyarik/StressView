#include "pointinfo.h"

PointInfo::PointInfo(int val, int time, int curtemp, bool bad)
    : m_val(val), m_time(time), m_curtemp(curtemp), m_bad(bad) {}

int PointInfo::getVal() const
{
    return m_val;
}

int PointInfo::getTime() const
{
    return m_time;
}

int PointInfo::getTemp() const
{
    return m_curtemp;
}

bool PointInfo::isBad() const
{
    return m_bad;
}
