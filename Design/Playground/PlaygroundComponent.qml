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
            // New input to parse
        }
    }
    ColumnLayout {
        width: parent.width
        CoreLabel {
            text: "Write whatever you want"
        }
        CoreButton {
            text: "pinMode 9 OUTPUT"
            Timer {
                id: delayTimer
                interval: 2000  // 2 seconds
                repeat: false
                onTriggered: {
                    // 2 seconds have passed
                    if (Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED) {
                        Constants.mytype.writeKeys("pinMode 9 OUTPUT\n")
                    }

                }
            }
            onClicked: {
                Constants.mytype.openSerialPort()
                delayTimer.start()
            }
        }
        CoreLabel {
            text: "analogWrite 9 " + parseInt( sliderId.value)
        }

        CoreSlider {
            id: sliderId
            Layout.fillWidth: true
            from: 0
            value: 0
            to: 255
            onMoved: ()=>{
                Constants.mytype.writeKeys("analogWrite 9 " + parseInt( sliderId.value) + "\n")
            }
        }
    }



}

