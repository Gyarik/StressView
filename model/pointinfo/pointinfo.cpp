#include "pointinfo.h"

PointInfo::PointInfo(int time, int curtemp, bool bad)
    : m_time(time), m_curtemp(curtemp), m_bad(bad) {}

PointInfo::~PointInfo() {}

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
