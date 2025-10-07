

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
    id: screenId
    width: parent.width
    height: parent.height
    Layout.fillWidth: true
    GroupBox {
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreButton {
                onClicked: {
                    console.log("clicked")
                    console.log(Constants.mytype.settingsConn.name)
                    //Constants.mytype.printSerialPorts()
                    //Constants.mytype.openSerialPort()
                    //Constants.mytype.writeShalom()
                    //Constants.mytype.closeSerialPort()
                    //Constants.mytype.asyncConnectArduino((s)=>{console.log(s)})
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
                    loaderId.sourceComponent = terminalSettingsId
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

    Loader  {
        id: loaderId
        Layout.fillWidth: true
        Layout.fillHeight: true
        sourceComponent: terminalBodyId

    }
    Component {
        id: terminalBodyId
        Column  {

            CoreTextArea {
                Layout.margins:  CoreSystemPalette.font.pixelSize
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "the text"
            }
        }
    }

    Component {
        id: terminalSettingsId
        Column  {
            GridLayout {
                columns: 2
                CoreButton {
                    Layout.leftMargin:   CoreSystemPalette.font.pixelSize
                    Layout.rightMargin:    CoreSystemPalette.font.pixelSize
                    Layout.columnSpan: 2
                    onClicked: {
                        loaderId.sourceComponent = terminalBodyId
                    }
                    text: "back"
                }
                CoreLabel {
                    Layout.leftMargin:   CoreSystemPalette.font.pixelSize
                    Layout.rightMargin:    CoreSystemPalette.font.pixelSize
                    text: "Select Serial Port"
                }

                CoreLabel {
                    text: "Select Parameters"
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignTop

                    GroupBox {
                        id: leftGtoupboxId
                        Layout.alignment: Qt.AlignTop
                        Layout.margins:  CoreSystemPalette.font.pixelSize
                        Layout.fillWidth: true
                        ColumnLayout {
                            CoreComboBox {
                                id: serialPortInfoListBox
                                model: ["dummy1","dummy2"]
                            }
                            CoreLabel {
                                text: "Description:"
                            }
                            CoreLabel {
                                text: "Manufacturer:"
                            }
                            CoreLabel {
                                text: "Serial number:"
                            }
                            CoreLabel {
                                text: "Location:"
                            }
                            CoreLabel {
                                text: "Vendor ID:"
                            }
                            CoreLabel {
                                text: "Product ID:"
                            }

                        }
                    }

                }

                ColumnLayout {

                    Layout.fillWidth: true

                    GroupBox {
                        Layout.fillWidth: true
                        Layout.rightMargin:   CoreSystemPalette.font.pixelSize
                        height: leftGtoupboxId.height

                        ColumnLayout {
                            RowLayout {
                                CoreLabel {
                                    text: "BaudRate"
                                }

                                CoreTextField {
                                    text: "6600"
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Data bits"
                                }

                                CoreTextField {
                                    text: "8"
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "parity"
                                }
                                CoreComboBox {
                                    model: ["None","Even","Odd","Mark","Space"]
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Stop bits"
                                }
                                CoreComboBox {
                                    model: ["1","2"]
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Flow control"
                                }
                                CoreComboBox {
                                    model: ["None","RTS/CTS","XON/XOFF"]
                                }
                            }
                        }
                    }

                }


                CoreLabel {
                    Layout.columnSpan:  2
                    Layout.margins:  CoreSystemPalette.font.pixelSize
                    text: "Additional options"
                }
                GroupBox {
                    Layout.alignment: Qt.AlignTop
                    Layout.columnSpan: 2
                    Layout.margins:  CoreSystemPalette.font.pixelSize
                    Layout.fillWidth: true
                    CoreCheckBox {
                        text: "Local echo"
                    }
                }
            }

        }


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


}
