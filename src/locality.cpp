#include "locality.h"

Locality::Locality(QObject* parent)
    : QObject(parent), m_gpsInfo(new GpsInfoProvider)
{
    m_gpsInfo->setActive(true);
    connect(m_manegerLocalityRequest, &LocalityRequest::geocoderResponse, this, &Locality::receiveGeocoderResponse);
    connect(m_gpsInfo, &GpsInfoProvider::newCoordinate, this, &Locality::coordinateChanged);

}
void Locality::searchLocation(QString search){
    m_manegerLocalityRequest->searchLocality(search);
}

void Locality::coordinateChanged(QGeoCoordinate coordinate){

    if(coordinate.longitude()!=0 && coordinate.latitude()!=0){
        emit newCoordinate(coordinate.longitude(), coordinate.latitude());
    }

}

void Locality::receiveGeocoderResponse(QByteArray answer){
    m_localitySearchParser.runParsingXml(answer);
    m_searchCities = m_localitySearchParser.getListLocation();
}

void Locality::addSelectedCity(LocalityStruct newSelected){

    m_selectedCities.append(newSelected);
    //TODO добавить добавление в бд
    emit selectedCitiesChanges();
}
void Locality::removeSelectedCity(LocalityStruct removeSelected){
    m_selectedCities.removeAll(removeSelected);
    //TODO добавить добавление в бд
    emit selectedCitiesChanges();
}
