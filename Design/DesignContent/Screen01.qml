

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
import Playground

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

    HeaderComponent {
        id: headerComponentId
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
        TerminalBodyComponent {

        }
    }

    Component {
        id: terminalSettingsId
        TerminalSettingsComponent {
            Layout.fillWidth: true
        }
    }

    Component {
        id: playgroundId
        PlaygroundComponent  {

        }
    }

    StatusBarComponent {
        Layout.fillWidth: true
        Layout.margins: CoreSystemPalette.font.pixelSize
    }


}
