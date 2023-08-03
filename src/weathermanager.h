#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H
#include <QObject>

#include "weatherrequest.h"

class WeatherManager: public QObject
{
    Q_OBJECT

public:
    explicit WeatherManager(QObject* parent = 0);
    Q_INVOKABLE void requestWeather();

signals:
    void newWeather(QString weatherNow);
    void coordinateChanged(double longtitude, double latitude);

private:
    WeatherRequest* weatherRequestManager;
    QString m_stringWeather;

private slots:
    void weatherChanged(QByteArray data);
};

#endif // WEATHERMANAGER_H

