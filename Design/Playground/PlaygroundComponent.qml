import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal
import QtCharts


Column  {


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
                if (Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED) {
                    Constants.mytype.openSerialPort()
                }
                delayTimer.start()
            }
        }

    }



}

