#include "pointinfo.h"

template <typename T> PointInfo<T>::PointInfo(T val, int time, int curtemp, bool bad)
    : m_val(val), m_time(time), m_curtemp(curtemp), m_bad(bad) {}

template <typename T> T PointInfo<T>::getValue() const
{
    return m_val;
}

template <typename T> int PointInfo<T>::getTime() const
{
    return m_time;
}

template <typename T> int PointInfo<T>::getTemp() const
{
    return m_curtemp;
}

template <typename T> bool PointInfo<T>::isBad() const
{
    return m_bad;
}

template class PointInfo<int>;
template class PointInfo<float>;
