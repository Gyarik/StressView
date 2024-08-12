#include "pointinfo.h"

template <typename T> PointInfo<T>::PointInfo(T val, int time, bool bad)
    : m_val(val), m_time(time), m_bad(bad) {}

template <typename T> T PointInfo<T>::getValue() const
{
    return m_val;
}

template <typename T> int PointInfo<T>::getTime() const
{
    return m_time;
}

template <typename T> bool PointInfo<T>::isBad() const
{
    return m_bad;
}
