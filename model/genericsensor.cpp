#include "genericsensor.h"

//template <typename T>
GenericSensor::GenericSensor(const string &name, const string &desc, int max, int temp)
    : m_name(name), m_desc(desc), m_max(max), m_temp(temp) {}

// template <typename T> GenericSensor<T>::~GenericSensor() {}

// template <typename T> void GenericSensor<T>::populate() {}

// template class GenericSensor<int>;
// template class GenericSensor<float>;
