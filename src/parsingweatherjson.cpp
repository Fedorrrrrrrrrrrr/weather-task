#include "parsingweatherjson.h"
#include <string>


ParsingWeatherJson::ParsingWeatherJson(QObject* parent)
    : QObject(parent)
{

}
void ParsingWeatherJson::goParsingJsonObjWeather(QString m_stringWeather){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_stringWeather.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    m_weather.m_city = jsonObj.find("name").value().toString();

    m_weather.m_temperature = jsonObj.find("main")->toObject().find("temp").value().toDouble();
    m_weather.m_pressure = jsonObj.find("main")->toObject().find("pressure").value().toInt();
    m_weather.m_humidity = jsonObj.find("main")->toObject().find("humidity").value().toInt();
    m_weather.m_icon =  jsonObj.find("weather")->toArray()[0].toObject().find("icon").value().toString();
    m_weather.m_time = jsonObj.find("main").value().toInt();
}
