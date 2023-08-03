#include "cachedb.h"

CacheDb::CacheDb(QObject* parent): QObject(parent)
{

}

void CacheDb::openDb(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("testHost");
    db.setDatabaseName("my_db.sqlite");
    db.setUserName("testUser");
    db.setPassword("testPassword");

    if (!db.open()) {
       qDebug() << "Error creating database!";
       }
}
void CacheDb::creatingTables(){
    openDb();
    QSqlQuery creatingTableCitiesQuery;
    QString strcreatingTableCitiesQuery = "CREATE TABLE selected_cities ("
            "id VARCHAR(255) PRIMARY KEY NOT NULL, "
            "address VARCHAR(255), "
            "locaklity VARCHAR(255), "
            "administrativeArea VARCHAR(255), "
            "longitude double, "
            "latitude double, "
            ");";
    bool b = creatingTableCitiesQuery.exec(strcreatingTableCitiesQuery);
    if (!b) {
        qDebug() << "Error creating cities table!";
    }
    QSqlQuery creatingTableWeatherQuery;
    QString strQuery = "CREATE TABLE weather ("
            "id VARCHAR(255) PRIMARY KEY NOT NULL, "
            "icon VARCHAR(255), "
            "city VARCHAR(255), "
            "temperature double, "
            "pressure integer, "
            "humidity integer, "
            "city_id integer, "
            "FOREIGN KEY (city_id)  REFERENCES selected_cities (id)"
            ");";

    bool b2 = creatingTableWeatherQuery.exec(strQuery);
    if (!b2) {
        qDebug() << "Error creating table!";
    }
    db.close();
}

void CacheDb::insertCity(LocalityStruct city){

    QSqlQuery a_query;


    QString strInsert = "INSERT INTO selected_cities(id, address, locaklity, administrativeArea, longitude, latitude) "
               "VALUES (%1, '%2', %3, %4, %5, %6);";
    QString str = strInsert.arg(city.m_locaklity+";"+ QString::number(city.m_longitude)+";"+QString::number(city.m_latitude))
            .arg(city.m_adress)
            .arg(city.m_locaklity)
            .arg(city.m_administrativeArea)
            .arg(city.m_longitude)
            .arg(city.m_latitude);
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Error insert city data!";
    }
}
void CacheDb::insertWeather(WeatherStruct weather){
    openDb();
    QSqlQuery a_query;
    QSqlQuery query;
    QString cityId;
    query.exec("SELECT id FROM selected_cities WHERE locaklity == weather.city");

    while (query.next()) {
        cityId = query.value(0).toString();
    }


    QString strInsert = "INSERT INTO weather(id, address, locaklity, administrativeArea, longitude, latitude) "
               "VALUES (%1, '%2', %3, %4, %5, %6);";
    QString str = strInsert.arg(QString::number(weather.m_time)+";"+weather.m_city)
            .arg(weather.m_icon)
            .arg(weather.m_city)
            .arg(weather.m_temperature)
            .arg(weather.m_pressure)
            .arg(weather.m_time)
            .arg(weather.m_humidity)
            .arg(cityId);
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Error insert weather data!";
    }
    db.close();
}

QList<LocalityStruct> CacheDb::getCitiesTable(){
    openDb();
    QList<LocalityStruct> listCities;
    QSqlQuery query;
    QString strQuery = "SELECT * FROM selected_cities";
    query.exec(strQuery);

    while (query.next()) {
        LocalityStruct item;
        item.m_adress = query.value(1).toString();
        item.m_locaklity = query.value(2).toString();
        item.m_administrativeArea = query.value(3).toString();
        item.m_longitude = query.value(4).toDouble();
        item.m_latitude = query.value(5).toDouble();
        listCities.append(item);
        }
    db.close();
    return  listCities;
}

WeatherStruct CacheDb::getWeatherForCity(LocalityStruct city){
    openDb();
    QSqlQuery query;
    QString strQuery = "SELECT * FROM weather WHERE city_id %1";
    QString str = strQuery.arg(city.m_locaklity+";"+ QString::number(city.m_longitude)+";"+QString::number(city.m_latitude));
    query.exec(str);

    WeatherStruct item;
    while (query.next()) {

        item.m_icon = query.value(1).toString();
        item.m_city = query.value(2).toString();
        item.m_temperature = query.value(3).toDouble();
        item.m_pressure = query.value(4).toInt();
        item.m_humidity = query.value(5).toInt();
        }
    db.close();
    return item;
}


