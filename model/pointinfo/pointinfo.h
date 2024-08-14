#ifndef POINTINFO_H
#define POINTINFO_H

class PointInfo
{
private:
    int m_time;
    int m_curtemp;
    bool m_bad;

public:
    PointInfo(int = 0, int = 40, bool = false);
    virtual ~PointInfo() = 0;
    int getTime() const;
    int getTemp() const;
    bool isBad() const;
};

#endif
