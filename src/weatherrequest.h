#ifndef WEATHERREQUEST_H
#define WEATHERREQUEST_H

#include <QObject>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>




class WeatherRequest: public QObject

{
    Q_OBJECT

public:
    explicit WeatherRequest(QObject* parent = 0);
    QString getJsonStrWeather(){return m_jsonStr;};
    void checkWeather();
    void coordinateChanged(double longtitude, double latitude);

signals:
    void currentStrChanged(QByteArray answer);

public slots:
    void replyFinished(QNetworkReply *);

private:
    QString m_jsonStr;
    QNetworkAccessManager *manager;
    QJsonObject m_jsonObj;
    double m_lon = 55.75396;
    double m_lat = 37.620393;
    QString m_lang = "ru_RU";
    QString m_extra = "true";
    QByteArray m_Key = "d724332725151eebc7ba9cc86266029a";

};

#endif // WEATHERREQUEST_H
