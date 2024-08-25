#ifndef POINTINFO_H
#define POINTINFO_H

class GenericPointVisitor;

class PointInfo
{
private:
    int m_val;
    int m_time;
    int m_curtemp;
    bool m_bad;

public:
    PointInfo(int = 0, int = 0, int = 40, bool = false);
    int getVal() const;
    int getTime() const;
    int getTemp() const;
    bool isBad() const;
};

#endif
