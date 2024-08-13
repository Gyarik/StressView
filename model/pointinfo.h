#ifndef POINTINFO_H
#define POINTINFO_H

template <typename T> class PointInfo
{
private:
    T m_val;
    int m_time;
    int m_curtemp;
    bool m_bad;

public:
    PointInfo(T = 0, int = 0, int = 40, bool = false);
    T getValue() const;
    int getTime() const;
    int getTemp() const;
    bool isBad() const;
};

#endif
