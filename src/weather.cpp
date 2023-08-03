#include "weather.h"
#include <QDateTime>

Weather::Weather(QObject* parent)
   : QObject(parent), m_weatherParser(new ParsingWeatherJson)
{

}


void Weather::weatherChanged(QString weatherNow){
    m_weatherParser.goParsingJsonObjWeather(weatherNow);
    m_weather = m_weatherParser.getWeather();
    emit structChanged();
};
