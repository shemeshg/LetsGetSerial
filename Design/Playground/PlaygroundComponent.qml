import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal
import QtCharts
import QtQuick.Dialogs


Column  {


    Connections {
        target: Constants.mytype
        function onAddTextToConsole(s) {
            myDummyTextField.text = s;
        }
    }
    ColumnLayout {
        CoreButton {
            text: "Start"
            Timer {
                id: delayTimer
                interval: 2000  // 2 seconds
                repeat: false
                onTriggered: {
                    // 2 seconds have passed
                    if (Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED) {
                        Constants.mytype.writeKeys("pinMode 9 OUTPUT\n")
                        Constants.mytype.writeKeys("pinMode 10 OUTPUT\n")
                        Constants.mytype.writeKeys("pinMode 11 OUTPUT\n")
                    }

                }
            }
            onClicked: {
                if (Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED) {
                    Constants.mytype.openSerialPort()
                }
                delayTimer.start()


            }
        }
        CoreLabel {
            id: myDummyTextField
            text: "example response you may parse\nPaint a graph or whatever"
        }
     }

    ColorDialog {
        id: colorDialog
        selectedColor:  "black"
        onAccepted: {
            let r = parseInt(selectedColor.r * 255)
            let g = parseInt(selectedColor.g * 255)
            let b = parseInt(selectedColor.b * 255)
            Constants.mytype.writeKeys("analogWrite 9 " + g + "\n")
            Constants.mytype.writeKeys("analogWrite 10 " + r + "\n")
            Constants.mytype.writeKeys("analogWrite 11 " + b + "\n")

            console.log("r:", r, "g:", g, "b:", b)
        }
    }
    CoreButton {
        onClicked: colorDialog.open()
        text: "Pick color"
    }

    Rectangle {
        id: displayedColorId
        color: colorDialog.selectedColor
        width: 40; height: 40
    }
}

