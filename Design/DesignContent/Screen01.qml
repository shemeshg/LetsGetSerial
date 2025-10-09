

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
import Bal

ColumnLayout {
    id: screenId
    width: parent.width
    height: parent.height
    Layout.fillWidth: true




    Connections {
        target: Constants.mytype
        function onAddTextToConsole(s) {
            loaderId.consoleLogStr += s;
            loaderId.moveEndTextArea();
        }
    }

    GroupBox {
        visible: loaderId.sourceComponent === terminalSettingsId
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreButton {
                Layout.leftMargin:   CoreSystemPalette.font.pixelSize /2
                Layout.rightMargin:    CoreSystemPalette.font.pixelSize
                onClicked: {
                    loaderId.sourceComponent = terminalBodyId
                }
                text: "back"
            }
        }
    }
    GroupBox {
        visible: loaderId.sourceComponent !== terminalSettingsId
        Layout.margins:  CoreSystemPalette.font.pixelSize
        Layout.fillWidth: true
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            CoreButton {
                enabled: Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED
                onClicked: {
                    Constants.mytype.openSerialPort()
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
                enabled: Constants.mytype.connStatus === MyType.ConnStatus.CONNECTED
                onClicked: {
                    Constants.mytype.closeSerialPort()
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
                enabled: Constants.mytype.connStatus !== MyType.ConnStatus.CONNECTED
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
                    Qt.quit()
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

        property string consoleLogStr: "";

        signal moveEndTextArea()

    }
    Component {
        id: terminalBodyId
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
                                               // event.accepted = false;
                                                consoleLogStr += event.text;
                                            }
                                            event.accepted = true;

                                            Constants.mytype.writeKey(event.text);
                                        }
                                    }
                }
            }
        }

    }

    Component {
        id: terminalSettingsId
        Column  {
            Layout.fillWidth: true
            GridLayout {
                width: parent.width
                columns: 2

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
                                id: serialPortId
                                model: Constants.mytype.getSerialPorts()
                                implicitContentWidthPolicy: ComboBox.WidestText
                                textRole: "portName"
                                valueRole: "portName"
                                onCurrentValueChanged:  {
                                    Constants.mytype.settingsConn.serialPortName = currentValue
                                }

                            }
                            CoreLabel {
                                text: "Description: " +
                                      serialPortId.model[serialPortId.currentIndex].description
                            }
                            CoreLabel {
                                text: "Manufacturer:" +
                                      serialPortId.model[serialPortId.currentIndex].manufacturer
                            }
                            CoreLabel {
                                text: "Serial number:" +
                                      serialPortId.model[serialPortId.currentIndex].serialNumber
                            }
                            CoreLabel {
                                text: "Location:" +
                                      serialPortId.model[serialPortId.currentIndex].systemLocation
                            }
                            CoreLabel {
                                text: "Vendor ID:" +
                                      serialPortId.model[serialPortId.currentIndex].vendorId
                            }
                            CoreLabel {
                                text: "Product ID:" +
                                      serialPortId.model[serialPortId.currentIndex].productId
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

                                CoreComboBox  {
                                    model: Constants.mytype.settingsConn.getBaudRateBox()
                                    textRole: "str"
                                    valueRole: "val"
                                    currentValue: Constants.mytype.settingsConn.baudRate
                                    onCurrentValueChanged:  {
                                        Constants.mytype.settingsConn.baudRate = currentValue
                                    }
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Data bits"
                                }

                                CoreComboBox  {
                                    model: Constants.mytype.settingsConn.getDataBitsBox()
                                    textRole: "str"
                                    valueRole: "val"
                                    currentValue: Constants.mytype.settingsConn.dataBits
                                    onCurrentValueChanged:  {
                                        Constants.mytype.settingsConn.dataBits = currentValue
                                    }
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "parity"
                                }
                                CoreComboBox {
                                    model: Constants.mytype.settingsConn.getParityBox()
                                    textRole: "str"
                                    valueRole: "val"
                                    currentValue: Constants.mytype.settingsConn.parity
                                    onCurrentValueChanged:  {
                                        Constants.mytype.settingsConn.parity = currentValue
                                    }
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Stop bits"
                                }
                                CoreComboBox {
                                    model: Constants.mytype.settingsConn.getStopBitsBox()
                                    textRole: "str"
                                    valueRole: "val"
                                    currentValue: Constants.mytype.settingsConn.stopBits
                                    onCurrentValueChanged:  {
                                        Constants.mytype.settingsConn.stopBits = currentValue
                                    }
                                }
                            }
                            RowLayout {
                                CoreLabel {
                                    text: "Flow control"
                                }
                                CoreComboBox {
                                    model: Constants.mytype.settingsConn.getFlowControlBox()
                                    textRole: "str"
                                    valueRole: "val"
                                    currentValue: Constants.mytype.settingsConn.flowControl
                                    onCurrentValueChanged:  {
                                        Constants.mytype.settingsConn.flowControl = currentValue
                                    }
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
                        checked: Constants.mytype.settingsConn.isLocalEcho
                        onToggled: {
                            Constants.mytype.settingsConn.isLocalEcho = checked
                        }

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
                text: Constants.mytype.statusText
            }
        }
    }


}
