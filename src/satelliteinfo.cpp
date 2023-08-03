#include "satelliteinfo.h"

SatelliteInfo::SatelliteInfo(const SatelliteInfo &other)
    : azimuth(other.azimuth), elevation(other.elevation), identifier(other.identifier),
      signalStrength(other.signalStrength), inUse(other.inUse)
{
}

SatelliteInfo::SatelliteInfo(qreal azimuth, qreal elevation, qint32 identifier, qint32 signalStrength, bool inUse)
    : azimuth(azimuth), elevation(elevation), identifier(identifier),
      signalStrength(signalStrength), inUse(inUse)
{
}
