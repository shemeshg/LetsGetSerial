import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal
import QtCharts


Column  {
    Connections {
        target: Constants.mytype
        function onAddTextToConsole(s) {
            s.split(/\r?\n/).forEach(line => {
              if (line === "LED STATUS: LOW") {
                ledImg.source = Qt.resolvedUrl("icons/LED_OFF.png")
              } else if (line === "LED STATUS: HIGH") {
                ledImg.source = Qt.resolvedUrl("icons/LED_ON.png");
              } else {
                //do nothing
              }
            });
        }
    }
    ColumnLayout {
        Image {
            id: ledImg
            source: Qt.resolvedUrl(
                        "icons/LED_OFF.png")
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100
            fillMode: Image.PreserveAspectFit
        }

        CoreButton {
            text: "Connect"
            Timer {
                id: delayTimer
                interval: 2000  // 2 seconds
                repeat: false
                onTriggered: {
                    // 2 seconds have passed
                    if (Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED) {
                        Constants.mytype.writeKeys("LED\n")
                    }

                }
            }
            onClicked: {
                Constants.mytype.openSerialPort()
                delayTimer.start()


            }
        }


    }



}

