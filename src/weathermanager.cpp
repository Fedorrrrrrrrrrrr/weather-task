#include "weathermanager.h"

WeatherManager::WeatherManager(QObject* parent):
    QObject(parent), weatherRequestManager(new WeatherRequest)
{
    connect(weatherRequestManager, &WeatherRequest::currentStrChanged, this, &WeatherManager::weatherChanged);

}

void WeatherManager::weatherChanged(QByteArray data){
    Q_UNUSED (data);
    m_stringWeather = weatherRequestManager->getJsonStrWeather();
    emit newWeather(m_stringWeather);
}

void WeatherManager::requestWeather(){
    weatherRequestManager->checkWeather();
}

void WeatherManager::coordinateChanged(double longtitude, double latitude){
    weatherRequestManager->coordinateChanged(longtitude, latitude);
    weatherRequestManager->checkWeather();
}
