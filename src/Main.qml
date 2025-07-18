import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Visual Algorithms")
    color: '#D9D9D9'
    Material.theme: Material.Dark

    NoiseCanvas {
        id: canvas
        anchors {
            top: parent.top
            left: parent.left
            margins: 30
        }
    }

    InputBar {
        id: inputBar
        height: parent.height
        anchors {
            top: parent.top
            right: parent.right
        }
    }
}
