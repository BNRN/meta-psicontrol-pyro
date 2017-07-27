import QtQuick 2.0
import QtQuick.Window 2.2

Window {
    id: colorMain
    objectName: "colorMain"

    signal reloadDone()

    function setSource( source ){
        mainLoader.setSource( source )
        console.log("source set")
        console.log(source)
    }
    visible: true
    width: Screen.width
    height: Screen.height

    Loader {
        anchors.fill: parent
        id: mainLoader
        objectName: "mainLoader"
        source: ""
        onLoaded: colorMain.reloadDone()
    }
}
