import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal

Column  {
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
