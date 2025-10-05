

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core

ColumnLayout {
    width: parent.width
    height: parent.height
    GroupBox {
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        RowLayout {
             anchors.left: parent.left
             anchors.right: parent.right
            CoreButton {
                onClicked: {
                    console.log("clicked")
                }
                icon.name: "Connect"
                icon.source: Qt.resolvedUrl(
                                 "icons/connect.png")
                hooverText: "Connect to serial port"
                icon.color: undefined
                isIconAnomation: false
                icon.width: CoreSystemPalette.font.pixelSize * 2
                icon.height: CoreSystemPalette.font.pixelSize * 2
            }
            CoreButton {
                onClicked: {
                    console.log("clicked")
                }
                icon.name: "Disconnect"
                icon.source: Qt.resolvedUrl(
                                 "icons/disconnect.png")
                hooverText: "Disconnect from serial port"
                icon.color: undefined
                isIconAnomation: false
                icon.width: CoreSystemPalette.font.pixelSize * 2
                icon.height: CoreSystemPalette.font.pixelSize * 2
            }
            CoreButton {
                onClicked: {
                    console.log("clicked")
                }
                icon.name: "Configure"
                icon.source: Qt.resolvedUrl(
                                 "icons/settings.png")
                hooverText: "Configure serial port"
                icon.color: undefined
                isIconAnomation: false
                icon.width: CoreSystemPalette.font.pixelSize * 2
                icon.height: CoreSystemPalette.font.pixelSize * 2
            }
            CoreButton {
                onClicked: {
                    console.log("clicked")
                }
                icon.name: "Clear"
                icon.source: Qt.resolvedUrl(
                                 "icons/clear.png")
                hooverText: "Clear data"
                icon.color: undefined
                isIconAnomation: false
                icon.width: CoreSystemPalette.font.pixelSize * 2
                icon.height: CoreSystemPalette.font.pixelSize * 2
            }
            CoreButton {
                onClicked: {
                    console.log("clicked")
                }
                icon.name: "Quit"
                icon.source: Qt.resolvedUrl(
                                 "icons/application-exit.png")
                hooverText: "Quit"
                icon.color: undefined
                isIconAnomation: false
                icon.width: CoreSystemPalette.font.pixelSize * 2
                icon.height: CoreSystemPalette.font.pixelSize * 2
            }
            Item {
                Layout.fillWidth: true
            }

        }
    }

    CoreTextArea {
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        Layout.fillHeight: true
        text: "the text"
    }

    GroupBox {
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        RowLayout {
             anchors.left: parent.left
             anchors.right: parent.right
             CoreLabel {
                 text: "status"
             }
        }
    }
    /*
    RowLayout {
        CoreButton {
            text: "printSerialPorts"
            onClicked: {
                Constants.mytype.printSerialPorts()
            }
        }
    }
    RowLayout {
        CoreButton {
            text: "openSerialPort"
            onClicked: {
                //Constants.mytype.asyncConnectArduino((s)=>{console.log(s)})
                Constants.mytype.openSerialPort()
            }
        }
    }
    RowLayout {
        CoreButton {
            text: "writeShalom"
            onClicked: {
                //Constants.mytype.asyncConnectArduino((s)=>{console.log(s)})
                Constants.mytype.writeShalom()
            }
        }
    }    
    RowLayout {
        CoreButton {
            text: "closeSerialPort"
            onClicked: {
                //Constants.mytype.asyncConnectArduino((s)=>{console.log(s)})
                Constants.mytype.closeSerialPort()
            }
        }
    }  


    RowLayout {
        CoreLabel {
            text: "Open serial "
        }
        CoreTextField {
            placeholderText: "Port name"
            Layout.fillWidth:true
        }
        CoreButton {
            text: "Connect getClicked"
            onClicked: {
                Constants.mytype.getClinked()
            }
        }
    }
    RowLayout {
        CoreLabel {
            text: "Connected to serial " + "COM3"
            Layout.fillWidth:true
        }
        CoreButton {
            text: "Connect"
        }
    }
    RowLayout {
        CoreLabel {
            text: "Error on serial " + "COM3"
            Layout.fillWidth:true
        }
        CoreButton {
            text: "Clear error"
        }
    }

    RowLayout {
        CoreLabel {
            text: "Send serial input"
        }
        CoreTextField {
            placeholderText: "Text to send"
            Layout.fillWidth:true
        }
        CoreButton {
            text: "Send"
        }
    }

    CoreButton {
        text: "Clear serial log"
    }
    CoreTextArea {
        text: "Serial output"
    }
    */

}
