#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

#include "weatherrequest.h"
#include <QJsonObject>
#include <QJsonValue>
#include "parsingweatherjson.h"
#include "sructWeather.h"
#include <QDir>

#include "sructWeather.h"


class Weather: public QObject
{
    Q_OBJECT

    Q_PROPERTY(WeatherStruct getWeather READ getWeather WRITE setWeather NOTIFY structChanged)

public:
    explicit Weather(QObject* parent = 0);

    Q_INVOKABLE WeatherStruct getWeather() const {return m_weather;}
    Q_INVOKABLE void setWeather(WeatherStruct val){m_weather = val;}


public slots:
     void weatherChanged(QString weatherNow);
signals:
    void structChanged();


private:
    ParsingWeatherJson m_weatherParser;
    WeatherStruct m_weather;

};

#endif // WEATHER_H

