import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Visual Algorithms")
    color: '#404040'
    Material.theme: Material.Dark

    /*TabBar {
        id: tabs
        width: parent.width
        TabButton {
            text: qsTr("1D Value")
        }
        TabButton {
            text: qsTr("+")
        }
    }
    StackLayout {
        width: parent.width
        currentIndex: tabs.currentIndex
        Item {
            id: value1DTab
        }
        Item {
            id: value2DTab
        }
    }*/

    Canvas {
        id: canvas
        width: 500
        height: 500
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 30

        onPaint: {
            var ctx = getContext("2d")
            ctx.fillStyle = "#FFFFFF"
            ctx.fillRect(0, 0, width, height)

            ctx.beginPath()
            var p = valueNoise.period;
            var s = valueNoise.steps();
            for (var i = 0; i < width; i++) {
                var x = i / (s - 1) * p
                var y = valueNoise.noise1D(x)
                ctx.lineTo(i, 3 * height / 4 - y * height / 2)
            }
            ctx.lineWidth = 2
            ctx.stroke()
        }
    }


    Rectangle {
        width: 200
        height: parent.height
        color: '#545454'
        anchors.top: parent.top
        anchors.right: parent.right

        Rectangle {
            id: periodRow
            width: parent.width
            height: 20
            color: 'transparent'
            anchors.top: parent.top
            anchors.margins: 20

            Text {
                width: 100
                height: 20
                font.pixelSize: 13
                anchors.top: parent.top
                anchors.left: parent.left
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: "period"
                color: '#FFFFFF'
            }

            TextField {
                background: Rectangle { color: '#404040' }
                color: '#FFFFFF'
                width: 50
                height: 20
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.rightMargin: 10

                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                bottomPadding: 0
                topPadding: 0

                text: valueNoise.period.toString()
                font.pixelSize: 12

                onEditingFinished: {
                    const newValue = parseInt(text)
                    if (!isNaN(newValue)) {
                        valueNoise.period = newValue
                        canvas.requestPaint()
                    }
                }
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            color: 'transparent'
            anchors {
                top: periodRow.bottom
                topMargin: 5
                leftMargin: 20
                rightMargin: 20
            }

            Text {
                width: 100
                font.pixelSize: 13
                anchors.top: parent.top
                anchors.left: parent.left
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: "seed"
                color: '#FFFFFF'
            }

            TextField {
                background: Rectangle { color: '#404040' }
                color: '#FFFFFF'
                width: 50
                height: 20
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.rightMargin: 10

                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter
                bottomPadding: 0
                topPadding: 0

                text: valueNoise.period.toString()
                font.pixelSize: 12

                onEditingFinished: {
                    const newValue = parseInt(text)
                    if (!isNaN(newValue)) {
                        valueNoise.seed = newValue
                        canvas.requestPaint()  // force redraw with new value
                    }
                }
            }
        }
    }
}
