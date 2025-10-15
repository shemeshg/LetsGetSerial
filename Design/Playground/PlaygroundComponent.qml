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
            if (s.startsWith("CHANGED: 14 ")){
                let v = s.split(" ")[2] / 4;
                sliderId.value = parseInt( v)
                sliderId.moved()
            }
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
                        Constants.mytype.writeKeys("pinMode 14 INPUT\n")
                        Constants.mytype.writeKeys("analogRead 14\n")
                        Constants.mytype.writeKeys("followMode 14 1 4 20\n")

                        Constants.mytype.writeKeys("pinMode 9 OUTPUTn")
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
