import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQml.Models 2.1

Page {
    id: locationPage
    allowedOrientations: Orientation.All
    Column{
        id: columnSettings
        spacing: Theme.paddingMedium
        width: locationPage.width
        height: locationPage.height
        //anchors.top:pageHeaderSettings.bottom
        PageHeader {
            id: pageHeader
            title: 'Местоположение'
            description :"Этот самый город"
        }
        TextField {
            id: searchLocation
            label: "SearchLocation"

            placeholderText: "Поиск"
            onPressAndHold: console.log("eeeee")
            onClicked: console.log(searchLocation.text)
            EnterKey.onClicked: {
                console.log(searchLocation.text)
                locality.searchLocation(searchLocation.text)
            }
        }

    }
    SilicaListView{
            id: searchResult
            model: locality.searchCities
            width: parent.width
            height: 400
            visible: searchLine.text.length > 0

            anchors{
                bottom: searchLocation.bottom
            }

            delegate:Column {
                MouseArea{
                    anchors.fill: parent
                    onClicked: console.log("test")
                    Label {
                        width:Theme.itemSizeExtraSmall
                        text: model.locaklity +"°C"
                        horizontalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                        color: Theme.highlightColor
                        fontSizeMode: Theme.fontSizeSmall
                    }
                }
            }

    }


}
