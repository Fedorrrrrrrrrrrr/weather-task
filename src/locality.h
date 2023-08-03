#ifndef LOCALITY_H
#define LOCALITY_H

#include <QObject>
#include "localityrequest.h"
#include "structLocality.h"
#include "gpsinfoprovider.h"
#include "parserxmllocation.h"

class Locality: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<LocalityStruct> searchCities READ getSearchCities
                    WRITE setSearchCities NOTIFY searchCitiesFilled)
    Q_PROPERTY(QList<LocalityStruct> selectedCities READ getSelectedCities
                    WRITE setSelectedCities NOTIFY selectedCitiesChanges)
public:
    explicit Locality(QObject* parent = 0);

    Q_INVOKABLE void searchLocation(QString search);
    Q_INVOKABLE QList<LocalityStruct> getSearchCities(){return m_searchCities;};
    Q_INVOKABLE void setSearchCities(QList<LocalityStruct> val){m_searchCities = val;};

    Q_INVOKABLE QList<LocalityStruct> getSelectedCities(){return m_selectedCities;};
    Q_INVOKABLE void setSelectedCities(QList<LocalityStruct> val){m_selectedCities = val;};
    Q_INVOKABLE void addSelectedCity(LocalityStruct newSelected);
    Q_INVOKABLE void removeSelectedCity(LocalityStruct removeSelected);


signals:
    void newCoordinate(double longtitude, double latitude);
    void searchCitiesChanges();
    void selectedCitiesChanges();

private slots:
    void coordinateChanged(QGeoCoordinate coordinate);
    void receiveGeocoderResponse(QByteArray answer);

private:
    LocalityRequest* m_manegerLocalityRequest;
    LocalityStruct m_selectLocality;
    GpsInfoProvider* m_gpsInfo;
    QList<LocalityStruct> m_selectedCities;
    QList<LocalityStruct> m_searchCities;
    ParserXmlLocation m_localitySearchParser;
};

#endif // LOCALITY_H
