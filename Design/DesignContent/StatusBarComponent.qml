import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Design
import Core
import Bal

GroupBox {
    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        CoreLabel {
            text: Constants.mytype.statusText
        }
    }
}
