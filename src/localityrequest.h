#ifndef LOCALITYREQUEST_H
#define LOCALITYREQUEST_H
#include <QObject>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include "parserxmllocation.h"
#include "structLocality.h"

class LocalityRequest: public QObject

{
    Q_OBJECT

public:
    LocalityRequest(QObject* parent = 0);
    Q_INVOKABLE void searchLocality(QString search);

private:
    QNetworkAccessManager *manager;
    QString m_yandexKey = "87dba37c-aff0-4ada-89a3-066b633ef7fd";
    QString m_wordSearch="Moscow";
    QString m_kind = "locality";
    QString m_format = "xml";
    QString m_result = "5";
    QString m_lang = "en_RU";

    QString m_lon = "55.75396";
    QString m_lat ="37.620393";
    ParserXmlLocation parserXml;
signals:
    void geocoderResponse(QByteArray answer);
public slots:
    void replyFinished(QNetworkReply *);
};

#endif // LOCALITYREQUEST_H
