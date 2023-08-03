#include "weatherrequest.h"
#include <QDebug>



WeatherRequest::WeatherRequest(QObject* parent)
    : QObject(parent)
{
    checkWeather();
}

void WeatherRequest::coordinateChanged(double longtitude, double latitude){
    m_lat = latitude;
    m_lon = longtitude;
    checkWeather();
}


void WeatherRequest::replyFinished(QNetworkReply *reply)
{
  emit currentStrChanged(reply->readAll());
}

void WeatherRequest::checkWeather()
{
  QString url = "https://api.openweathermap.org/data/2.5/weather?";
  QUrl qrl(url);
  QUrlQuery query;

  query.addQueryItem( "lat", QString::number(m_lon));
  query.addQueryItem( "lon", QString::number(m_lat));
  query.addQueryItem( "appid", m_Key);
  qrl.setQuery(query.query());
  QNetworkRequest request(qrl);

  manager = new QNetworkAccessManager(this);
  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

  manager->get(request);
}
