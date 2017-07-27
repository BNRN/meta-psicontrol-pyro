import QtQuick 2.3
import QtQuick.Window 2.2

Rectangle {
    id: colorTest
    objectName: "colorTest"
    property var logInfo : {
        "red" : "nok",
        "blue": "nok",
        "black": "nok",
        "green": "nok"
    }
    signal finishTest(var logInfo)

    function nextStep( result ){
        if( square.colorName === "red")
        {
            logInfo.red = result;
            square.colorName = "blue"
            square.color = "blue"
        }
        else if ( square.colorName === "blue")
        {
            logInfo.blue = result;
            square.colorName = "green"
            square.color = "green"
        }
        else if ( square.colorName === "green")
        {
            logInfo.green = result;
            square.colorName = "black"
            square.color = "black"
            square.border.color = "white"
            buttonText.color = "white"
            middle.border.color = "white"
            middleText.color = "white"

        }
        else
        {
            logInfo.black = result;
            squareMouseArea.enabled = false;
            middleArea.enabled = false;
            finishTest(logInfo);
        }
    }

    width: Screen.width
    height: Screen.height

    Rectangle {
        id: mainBox
        anchors.fill: parent
        color: square.color

        Connections {
            target : squareMouseArea
            onClicked: {
            if( square.colorName === "blue"){
                square.anchors.left = undefined;
                square.anchors.right = mainBox.right;
            }
            else if( square.colorName === "green"){
                square.anchors.top = undefined;
                square.anchors.bottom = mainBox.bottom;
            }
            else if( square.colorName === "black"){
                square.anchors.right = undefined;
                square.anchors.left = mainBox.left;
            }
            }
        }
        Connections {
            target: middleArea
            onClicked: {

                 nextStep("nok")
            }
        }

        Rectangle {
            id: square
            property  string colorName: "red"
            width: buttonText.width + 10; height: 120
            anchors.top: parent.top; anchors.left: parent.left; anchors.margins: 10
            color: "red"
            opacity: squareMouseArea.containsPress ? 0.6 : 1.0
            border.color: "black"
            border.width: 2
            Text { id:buttonText; text: "Click if color is " + square.colorName; font.pixelSize: 16; anchors.centerIn: parent }

            MouseArea {
                id: squareMouseArea
                anchors.fill: parent
                hoverEnabled: true
                property string buttonID

                acceptedButtons: Qt.AllButtons

                onPressed: {
                    nextStep("ok")
                }
            }
        }
        Rectangle{
            id: middle
            anchors.centerIn: parent;
            border.color: "black"
            border.width: 2
            width: 250
            height: 100
            color: square.color
            Text {
                id:middleText; text: "Click here if color is  NOK "; font.pixelSize: 16; anchors.centerIn: parent

            }
            MouseArea {
                id: middleArea
                anchors.fill: parent
            }

        }

    }
}
