#ifndef SENSORCONTAINER_H
#define SENSORCONTAINER_H
#include <vector>
#include <string>

using std::vector;
using std::string;

class GenericSensor;

class SensorContainer
{
private:
    static vector<GenericSensor *> m_cont;

public:
    // Container related methods
    static void emptyContainer();
    static const vector<GenericSensor *> & getContainer();

    // Sensor related methods
    bool addSensor(GenericSensor *);
    static void removeSensor(GenericSensor *);
    void editSensor(GenericSensor *, const string &, const string &, int, int);

    // Search function
    GenericSensor * searchSensor(const string &) const;

    // Check for same name
    bool isEqual(const string &, const string &) const;
};

#endif
