################################################################################
##
## Copyright (C) 2022 ru.auroraos
## 
## This file is part of the Приложение погоды для авроры project.
##
## Redistribution and use in source and binary forms,
## with or without modification, are permitted provided
## that the following conditions are met:
##
## * Redistributions of source code must retain the above copyright notice,
##   this list of conditions and the following disclaimer.
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer
##   in the documentation and/or other materials provided with the distribution.
## * Neither the name of the copyright holder nor the names of its contributors
##   may be used to endorse or promote products derived from this software
##   without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
## IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
## FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
## OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS;
## OR BUSINESS INTERRUPTION)
## HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
## WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
## EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
################################################################################

TARGET = ru.auroraos.AuroraWeather
i18n_files.files = img
i18n_files.path = /usr/share/$$TARGET

INSTALLS += i18n_files

CONFIG += \
    auroraapp

QT += \
    network \
    positioning \
    xml \
    sql


PKGCONFIG += \

SOURCES += \
    src/cachedb.cpp \
    src/gpsinfoprovider.cpp \
    src/locality.cpp \
    src/localityrequest.cpp \
    src/main.cpp \
    src/parserxmllocation.cpp \
    src/parsingweatherjson.cpp \
    src/satelliteinfo.cpp \
    src/weather.cpp \
    src/weathermanager.cpp \
    src/weatherrequest.cpp

HEADERS += \
    src/cachedb.h \
    src/gpsinfoprovider.h \
    src/locality.h \
    src/localityrequest.h \
    src/parserxmllocation.h \
    src/parsingweatherjson.h \
    src/satelliteinfo.h \
    src/sructWeather.h \
    src/structLocality.h \
    src/weather.h \
    src/weathermanager.h \
    src/weatherrequest.h

DISTFILES += \
    rpm/ru.auroraos.AuroraWeather.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.AuroraWeather.ts \
    translations/ru.auroraos.AuroraWeather-ru.ts \
