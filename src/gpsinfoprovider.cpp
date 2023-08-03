/*******************************************************************************
**
** Copyright (C) 2021-2022 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the Geolocation project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <QtPositioning/QGeoPositionInfoSource>
#include <QtPositioning/QGeoSatelliteInfoSource>

#include "gpsinfoprovider.h"

GpsInfoProvider::GpsInfoProvider(QObject *parent)
    : QObject(parent),
      m_positionSource(QGeoPositionInfoSource::createDefaultSource(this)),
      m_satelliteSource(QGeoSatelliteInfoSource::createDefaultSource(this)),
      m_active(false)
{
    if (m_positionSource){
        m_positionSource->setUpdateInterval(1000);
        connect(m_positionSource, &QGeoPositionInfoSource::positionUpdated,
                this, &GpsInfoProvider::_updatePositionInfo);
    }

    if (m_satelliteSource) {
        connect(m_satelliteSource, &QGeoSatelliteInfoSource::satellitesInUseUpdated,
                this, &GpsInfoProvider::_updateSatellitesInUse);
        connect(m_satelliteSource, &QGeoSatelliteInfoSource::satellitesInViewUpdated,
                this, &GpsInfoProvider::_updateSatellitesInView);
    }

    if (m_positionSource && m_positionSource->lastKnownPosition().isValid()) {
        m_positionInfo = m_positionSource->lastKnownPosition();
    }

}

bool GpsInfoProvider::active() const
{
    return m_active;
}

QVariantList GpsInfoProvider::satellites() const
{
    QVariantList result;
    QList<SatelliteInfo> satellitesInfo = m_satellites.values();
    for (const auto &satellite : satellitesInfo)
        result << QVariant::fromValue(satellite);

    return result;
}

qint32 GpsInfoProvider::satellitesInViewCount() const
{
    return m_satellites.count();
}

qint32 GpsInfoProvider::satellitesInUseCount() const
{
    auto result = 0;
    QList<SatelliteInfo> satellitesInfo = m_satellites.values();
    for (const auto &satellite : satellitesInfo) {
        if (satellite.inUse)
            result++;
    }

    return result;
}

QGeoCoordinate GpsInfoProvider::coordinate() const
{
    return m_positionInfo.coordinate();
}
QString GpsInfoProvider::longitude() const {
    return QString::number(m_positionInfo.coordinate().longitude());

}

QDateTime GpsInfoProvider::timestamp() const
{
    return m_positionInfo.timestamp();
}

qreal GpsInfoProvider::horizontalAccuracy() const
{
    return _geoPositionAttribute(QGeoPositionInfo::HorizontalAccuracy);
}

qreal GpsInfoProvider::verticalAccuracy() const
{
    return _geoPositionAttribute(QGeoPositionInfo::VerticalAccuracy);
}

QString GpsInfoProvider::direction() const
{
    qreal directionDegrees = _geoPositionAttribute(QGeoPositionInfo::Direction);
    if (directionDegrees < 0.0f)
        return "";
    else if (directionDegrees <= 22.0f || directionDegrees >= 338.0f)
        return tr("North");
    else if (directionDegrees <= 67.0f)
        return tr("Northeast");
    else if (directionDegrees <= 112.0f)
        return tr("East");
    else if (directionDegrees <= 157.0f)
        return tr("Southeast");
    else if (directionDegrees <= 202.0f)
        return tr("South");
    else if (directionDegrees <= 247.0f)
        return tr("Southwest");
    else if (directionDegrees <= 292.0f)
        return tr("West");
    else if (directionDegrees <= 337.0f)
        return tr("Northwest");
    return "";
}

qreal GpsInfoProvider::speed() const
{
    return _geoPositionAttribute(QGeoPositionInfo::GroundSpeed);
}

bool GpsInfoProvider::gpsEnabled() const
{
    if (!m_positionSource) {
        return false;
    }
    return m_positionSource->supportedPositioningMethods() != QGeoPositionInfoSource::NoPositioningMethods;
}

QString GpsInfoProvider::positioningMethod() const
{
    if (!m_positionSource) {
        return "";
    }
    switch (m_positionSource->supportedPositioningMethods()) {
    case QGeoPositionInfoSource::NoPositioningMethods:
        return "NoPositioningMethods";
    case QGeoPositionInfoSource::AllPositioningMethods:
        return tr("Satellite and network");
    case QGeoPositionInfoSource::NonSatellitePositioningMethods:
        return tr("Network");
    case QGeoPositionInfoSource::SatellitePositioningMethods:
        return tr("Satellite");
    default:
        return QStringLiteral("default");
    }
}

void GpsInfoProvider::setActive(bool active)
{
    if (m_active == active || !m_positionSource || !m_satelliteSource)
        return;

    if (active) {
        m_positionSource->startUpdates();
        m_satelliteSource->startUpdates();
    } else {
        m_positionSource->stopUpdates();
        m_satelliteSource->stopUpdates();
    }
    m_active = active;
    emit activeChanged();
}

void GpsInfoProvider::_updatePositionInfo(const QGeoPositionInfo &info)
{
    m_positionInfo = info;
    emit positionInfoChanged();
    emit newCoordinate(m_positionInfo.coordinate());
}

void GpsInfoProvider::_updateSatellitesInUse(const QList<QGeoSatelliteInfo> &satellitesInfo)
{
    for (const auto &satellite : satellitesInfo) {
        qint32 satId = satellite.satelliteIdentifier();
        if (m_satellites.contains(satId)) {
            m_satellites[satId].inUse = true;
        } else {
            _appendSatellite(satellite, true);
        }
    }
    emit satellitesChanged();
}

void GpsInfoProvider::_updateSatellitesInView(const QList<QGeoSatelliteInfo> &satellitesInfo)
{
    m_satellites.clear();
    for (const auto &satellite : satellitesInfo)
        _appendSatellite(satellite, false);
    emit satellitesChanged();
}

void GpsInfoProvider::_appendSatellite(const QGeoSatelliteInfo &satellite, bool inUse)
{
    m_satellites[satellite.satelliteIdentifier()] = SatelliteInfo(satellite.attribute(QGeoSatelliteInfo::Azimuth),
                                                                  satellite.attribute(QGeoSatelliteInfo::Elevation),
                                                                  satellite.satelliteIdentifier(),
                                                                  satellite.signalStrength(),
                                                                  inUse);
}

qreal GpsInfoProvider::_geoPositionAttribute(QGeoPositionInfo::Attribute attribute) const
{
    if (!m_positionInfo.hasAttribute(attribute))
        return -1;

    return m_positionInfo.attribute(attribute);
}

