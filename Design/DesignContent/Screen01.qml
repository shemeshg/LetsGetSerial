

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
    RowLayout {
        CoreLabel {
            text: qsTr("Hello Design ") + Constants.mytype.name

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
            text: "Connect"
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

}
