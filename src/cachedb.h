#ifndef CACHEDB_H
#define CACHEDB_H

#include <QtSql>
#include <QObject>
#include "sructWeather.h"
#include "structLocality.h"

class CacheDb: public QObject
{
    Q_OBJECT
public:
    explicit CacheDb(QObject* parent = 0);
    void openDb();
    void creatingTables();
    void insertCity(LocalityStruct city);
    void insertWeather(WeatherStruct weather);
    void removeCity(LocalityStruct city);
    void removeWeather(WeatherStruct weather);
    QList<LocalityStruct> getCitiesTable();
    WeatherStruct getWeatherForCity(LocalityStruct city);
    void closeDb();

private:
    QSqlDatabase db;
};

#endif // CACHEDB_H
