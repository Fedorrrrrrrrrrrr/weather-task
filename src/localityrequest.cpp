#include "localityrequest.h"

LocalityRequest::LocalityRequest(QObject* parent)
    : QObject(parent)
{

}
void LocalityRequest::replyFinished(QNetworkReply *reply)
{
    emit geocoderResponse(reply->readAll());
}

void LocalityRequest::searchLocality(QString search)
{

  QString url = "https://geocode-maps.yandex.ru/1.x?";
  QUrl qrl(url);
  QUrlQuery query;

  query.addQueryItem( "geocode",search);
  query.addQueryItem( "apikey", m_yandexKey);
  query.addQueryItem( "kind", m_kind);
  query.addQueryItem( "format", m_format);
  query.addQueryItem( "results", m_result);
  query.addQueryItem( "lang", m_lang);
  query.addQueryItem( "sco","longlat");

  qrl.setQuery(query.query());

  QNetworkRequest request(qrl);

  manager = new QNetworkAccessManager(this);

  connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

  manager->get(request);

}

