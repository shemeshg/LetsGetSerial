import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal


Column  {
    Layout.fillWidth: true
    ScrollView {
        width: parent.width
        height: parent.height
        Layout.fillWidth: true
        Layout.fillHeight: true

        CoreTextArea {
            width: parent.width
            wrapMode: TextEdit.WrapAnywhere
            Connections {
                target: loaderId
                function onMoveEndTextArea() {
                    consoleLogId.cursorPosition = consoleLogId.text.length;
                }

            }

            id: consoleLogId
            enabled: Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED
            Layout.margins:  CoreSystemPalette.font.pixelSize
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: consoleLogStr

            focus: true
            Keys.onPressed: (event)=>{
                                let localEchoEnabled = true;
                                switch (event.key) {
                                    case Qt.Key_Backspace:
                                    case Qt.Key_Left:
                                    case Qt.Key_Right:
                                    case Qt.Key_Up:
                                    case Qt.Key_Down:
                                    event.accepted = true;
                                    break;
                                    default:
                                    if (Constants.mytype.settingsConn.isLocalEcho) {

                                        consoleLogStr += event.text;
                                        consoleLogId.cursorPosition = consoleLogId.text.length;
                                    }
                                    event.accepted = true;

                                    Constants.mytype.writeKey(event.text);
                                }
                            }
        }
    }
}


