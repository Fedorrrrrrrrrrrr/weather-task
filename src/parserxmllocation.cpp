#include "parserxmllocation.h"
#include <QDomDocument>
#include <QDebug>


ParserXmlLocation::ParserXmlLocation()
{

}

void ParserXmlLocation::runParsingXml(QString xmlString){

    QDomDocument doc("mydocument");
    doc.setContent(xmlString);

    QDomNodeList listLocality = doc.elementsByTagName("featureMember");
    for(int i = 0; i<listLocality.size(); i++){

        QDomElement localityItem = listLocality.at(i).toElement();
        localityItem.elementsByTagName("pos").at(0).nodeValue();
        LocalityStruct item;
        item.m_administrativeArea = localityItem.elementsByTagName("SubAdministrativeAreaName").at(0).toElement().text();
        item.m_adress = localityItem.elementsByTagName("AddressLine").at(0).toElement().text();
        item.m_locaklity = localityItem.elementsByTagName("LocalityName").at(0).toElement().text();
        auto listCoordinate = localityItem.elementsByTagName("pos").at(0).toElement().text().split(" ");
        item.m_longitude = listCoordinate[1];
        item.m_latitude = listCoordinate[0];
        qDebug() << item.m_latitude <<item.m_longitude <<item.m_locaklity<<item.m_adress <<item.m_administrativeArea;
        m_listLocation.append(item);

    }
}
