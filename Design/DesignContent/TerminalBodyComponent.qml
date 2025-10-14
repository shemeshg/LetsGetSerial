import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal


Column  {
    Layout.fillWidth: true

    function doMoveToEndOfTextArea(){
        consoleLogId.cursorPosition = consoleLogId.text.length;
    }

    RowLayout{
        visible: Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED
        Layout.fillWidth: true
        width: parent.width
        CoreTextField {
            Layout.margins:  CoreSystemPalette.font.pixelSize
            Layout.fillWidth: true
            width: parent.width
            text: ""
            placeholderText: "Enter to submit"
            onAccepted: {
                Constants.mytype.writeKeys(text + "\n")
            }
        }
    }
    ScrollView {
        width: parent.width
        height: parent.height - CoreSystemPalette.font.pixelSize *2
        Layout.fillWidth: true
        Layout.fillHeight: true

        CoreTextArea {
            width: parent.width
            wrapMode: TextEdit.WrapAnywhere
            Connections {
                target: loaderId
                function onMoveEndTextArea() {
                    doMoveToEndOfTextArea();
                }

            }

            id: consoleLogId
            readOnly:  Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED
            Layout.margins:  CoreSystemPalette.font.pixelSize
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: consoleLogStr

            focus: true
            Keys.onPressed: (event)=>{


                                let localEchoEnabled = true;

                                // Check for Cmd+C (macOS) or Ctrl+C (Windows/Linux)
                                if ((event.modifiers & Qt.MetaModifier || event.modifiers & Qt.ControlModifier)
                                    ) {
                                    event.accepted = false;

                                    if (Qt.ControlModifier &&
                                                event.key === Qt.Key_V){

                                        if (Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED) {
                                            let pasteText = Constants.mytype.getClipboard()
                                            Constants.mytype.writeKeys(pasteText)
                                            if (Constants.mytype.settingsConn.isLocalEcho) {
                                                consoleLogStr += pasteText;
                                                doMoveToEndOfTextArea();
                                            }


                                            event.accepted = true;
                                        }

                                        return;
                                    }

                                    if (Qt.ControlModifier &&
                                                event.key !== Qt.Key_C){
                                        event.accepted = true;
                                        return;
                                    }


                                    return;
                                }

                                if (Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED){
                                    event.accepted = true;
                                    return;
                                }
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
                                        doMoveToEndOfTextArea();
                                    }
                                    event.accepted = true;

                                    Constants.mytype.writeKeys(event.text);
                                }
                            }
        }
    }
}


