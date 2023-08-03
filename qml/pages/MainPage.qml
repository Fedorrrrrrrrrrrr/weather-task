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
import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQml.Models 2.1
import ru.auroraos.weather 1.0


Page {
    id: mainPage
    allowedOrientations: Orientation.All

    PageHeader {
        id: pageHeader
        title: 'Weather Page'        
    }

    Button {
        id: buttonTransitionSearch
        anchors{
            right: parent.right
            top: pageHeader.bottom
        }

        text: qsTr("Search City")
        onClicked: pageStack.push(Qt.resolvedUrl("SearchCityPage.qml"))
    }


    Column{
       id: col
       spacing: Theme.paddingLarge
       width: mainPage.width
       anchors.top: buttonTransitionSearch.bottom

       Row {
           id: row1
           anchors.horizontalCenter: parent.horizontalCenter

           Label {
               id: city
               text: weather.getWeather.city
               wrapMode: Text.Wrap
               color: Theme.highlightColor
               fontSizeMode: Theme.fontSizeLarge
           }
       }

       Row {
           id: row2
           anchors.topMargin: Theme.paddingLarge
           anchors.horizontalCenter: parent.horizontalCenter

           Label {
               id: tempText
               text: weather.getWeather.temperature+"K"
               wrapMode: Text.Wrap
               color: Theme.primaryColor
               font.pixelSize: Theme.fontSizeHuge
           }
       }

       Row {
           id: row3
           anchors.topMargin: Theme.paddingLarge
           anchors.horizontalCenter: parent.horizontalCenter
           Image {
               width: Theme.iconSizeLarge; height: Theme.iconSizeLarge
               source: "/usr/share/ru.auroraos.AuroraWeather/img/"+weather.getWeather.icon+"@2x.png"
           }
       }

       Row {
           id: row4
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.topMargin: Theme.paddingLarge

           Label {
               id: humidity
               text: weather.getWeather.humidity + "% "
               wrapMode: Text.Wrap
               color: Theme.highlightColor
               fontSizeMode: Theme.fontSizeSmall
           }

           Label {
               id: pressure
               text: weather.getWeather.pressure +"millibars"
               wrapMode: Text.Wrap
               color: Theme.highlightColor
               fontSizeMode: Theme.fontSizeSmall
           }
       }
    }

    Column {
        id: row5
        width: mainPage.width
        anchors {
            bottom: mainPage.bottom
        }

        IconTextSwitch {
            id: citySwitch
            icon.source: checked ? "image://theme/icon-m-favorite-selected" : "image://theme/icon-m-favorite"
            text: checked ? qsTr("Сity Added") : qsTr("Сity Not Added")
            onClicked: console.log("Button clicked" + citySwitch.checked)
        }

        Button {
            id: buttonTransitionSelected
            anchors.right: parent.right
            text: qsTr("Selected Cities")
            onClicked: console.log("Button clicked")
        }
    }
}

