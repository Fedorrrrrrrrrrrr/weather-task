/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Приложение погоды для авроры project.
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

#include <auroraapp.h>
#include <QtQuick>
#include "gpsinfoprovider.h"
#include "weatherrequest.h"
#include "gpsinfoprovider.h"
#include "sructWeather.h"
#include "structLocality.h"
#include "localityrequest.h"
#include "weather.h"
#include "weathermanager.h"
#include "locality.h"

int main(int argc, char *argv[])
{


//    LocalityRequest test3;
//    test3.searchLocality("55°45.1332′ с.ш., 37°36.9336′ в.д.");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("AuroraWeather"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    qmlRegisterType<Weather>("ru.auroraos.weather", 1, 0, "Weather");
    qmlRegisterType<GpsInfoProvider>("ru.auroraos.weather", 1, 0, "GpsInfoProvider");
    qmlRegisterType<WeatherManager>("ru.auroraos.weather", 1, 0, "WeatherManager");
    qmlRegisterType<Locality>("ru.auroraos.weather", 1, 0, "Locality");
    qRegisterMetaType<WeatherStruct>();
    qRegisterMetaType<LocalityStruct>();

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/AuroraWeather.qml")));
    view->show();

    return application->exec();
}
