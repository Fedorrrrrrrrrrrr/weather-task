#ifndef PARSINGWEATHERJSON_H
#define PARSINGWEATHERJSON_H

#include <QObject>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDir>
#include <QtCore>
#include <QSettings>


#include "sructWeather.h"

class ParsingWeatherJson: public QObject
{
    Q_OBJECT
public:
    explicit ParsingWeatherJson(QObject* parent = 0);


    Q_INVOKABLE WeatherStruct getWeather(){return m_weather;};

    void goParsingJsonObjWeather(QString m_stringWeather);


private:
    WeatherStruct m_weather;

};

#endif // PARSINGWEATHERJSON_H
