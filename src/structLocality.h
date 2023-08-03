#ifndef STRUCTLOCALITY_H
#define STRUCTLOCALITY_H
#include <QObject>
struct LocalityStruct{
    Q_GADGET

    Q_PROPERTY(double longitude MEMBER m_longitude)
    Q_PROPERTY(double latitude MEMBER m_latitude)
    Q_PROPERTY(QString locaklity MEMBER m_locaklity)
    Q_PROPERTY(QString adress MEMBER m_adress)
    Q_PROPERTY(QString administrativeArea MEMBER m_administrativeArea)


public:
    QString m_longitude;
    QString m_latitude;
    QString m_locaklity;
    QString m_adress;
    QString m_administrativeArea;
};
Q_DECLARE_METATYPE(LocalityStruct)

#endif // STRUCTLOCALITY_H
