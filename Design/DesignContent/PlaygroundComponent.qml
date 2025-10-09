import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal



    Column  {
        Connections {
            target: Constants.mytype
            function onAddTextToConsole(s) {
                myDummyTextField.text = s;
            }
        }
        ColumnLayout {
            CoreLabel {
                text: "Write whatever you want"
            }
            CoreButton {
                text: "Example"
                Timer {
                    id: delayTimer
                    interval: 2000  // 2 seconds
                    repeat: false
                    onTriggered: {
                        // 2 seconds have passed
                        if (Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED) {
                            Constants.mytype.writeKeys("\n")
                        }

                    }
                }
                onClicked: {
                    Constants.mytype.openSerialPort()
                    delayTimer.start()


                }
            }
            CoreLabel {
                id: myDummyTextField
                text: "example response you may parse\nPaint a graph or whatever"
            }

        }
    }

