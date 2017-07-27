import QtQuick 2.0

Rectangle{

    function setErrorText( result){
        middleText.text = middleText.text + result
        console.log("set error")
        console.log(result)
    }
    objectName: "error"
    anchors.centerIn: parent;
    border.color: "black"
    border.width: 2
    width: 250
    height: 100
    Text {
        id:middleText; text: "Result : "; font.pixelSize: 16; anchors.centerIn: parent

    }
    Component.onCompleted: console.log("complete")

}
