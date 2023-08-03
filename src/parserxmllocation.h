#ifndef PARSERXMLLOCATION_H
#define PARSERXMLLOCATION_H
#include <QXmlStreamReader>
#include "structLocality.h"


class ParserXmlLocation
{
public:
    ParserXmlLocation();
    void runParsingXml(QString xmlString);

    QList<LocalityStruct> getListLocation() const {return m_listLocation;};
private:
    QList<LocalityStruct> m_listLocation;
};

#endif // PARSERXMLLOCATION_H
