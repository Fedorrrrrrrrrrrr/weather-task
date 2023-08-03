#ifndef SRUCTWEATHER_H
#define SRUCTWEATHER_H

#include <QObject>

struct WeatherStruct{

    Q_GADGET

    Q_PROPERTY(QString icon MEMBER m_icon)
    Q_PROPERTY(uint pressure MEMBER m_pressure)
    Q_PROPERTY(QString city MEMBER m_city)
    Q_PROPERTY(int time MEMBER m_time)
    Q_PROPERTY(double temperature MEMBER m_temperature)
    Q_PROPERTY(uint humidity MEMBER m_humidity)

public:
    QString m_icon;    
    uint m_pressure;
    QString m_city;
    int m_time;
    double m_temperature;
    uint m_humidity;
};
Q_DECLARE_METATYPE(WeatherStruct)

#endif // SRUCTWEATHER_H
