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
            for (var i = 0; i < s; i++) {
                var x = i / (s - 1) * p
                var y = valueNoise.noise1D(x)
                ctx.lineTo(i, 3 * height / 4 - y * height / 2)
            }
            ctx.lineWidth = 2
            ctx.stroke()
        }
    }

    Rectangle {
        width: 150
        height: parent.height
        color: '#FFFFFF'
        anchors {
            top: parent.top
            right: parent.right
        }

        ComboBox {
            id: comboBox
            height: 30
            width: parent.width
            anchors {
                top: parent.top
                topMargin: 10
                right: parent.right
                rightMargin: 10
                left: parent.left
                leftMargin: 10
            }
            font.pixelSize: 12
            bottomPadding: 0
            bottomInset: 0
            model: ["1D Value", "2D Value"]
            contentItem: Text {
                text: comboBox.displayText
                font: comboBox.font
                color: "black"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
            }

            background: Rectangle {
               radius: 2
               border.color: "#D9D9D9"
               color: "transparent"
            }
        }
        Text {
            id: periodText
            width: parent.width
            font.pixelSize: 10
            anchors {
                top: comboBox.bottom
                left: parent.left
                right: parent.right
                topMargin: 10
                leftMargin: 10
                rightMargin: 10
            }
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: "Period"
            color: '#8B8B8B'
        }

        TextField {
            id: periodField
            background: Rectangle {
                color: '#EDEDED'
                radius: 3
            }
            color: '#000000'
            width: parent.width
            height: 20
            anchors {
                top: periodText.bottom
                left: periodText.left
                right: periodText.right
                topMargin: 2
            }
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignRight
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

        Text {
            id: seedText
            width: parent.width
            font.pixelSize: 10
            anchors {
                top: periodField.bottom
                left: periodText.left
                right: periodText.right
                topMargin: 10
            }
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: "Seed"
            color: '#8B8B8B'
        }

        TextField {
            id: seedField
            background: Rectangle {
                color: '#EDEDED'
                radius: 3
            }
            color: '#000000'
            width: parent.width
            height: 20
            anchors {
                top: seedText.bottom
                left: seedText.left
                right: seedText.right
                topMargin: 2
            }
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignRight
            bottomPadding: 0
            topPadding: 0

            text: valueNoise.seed.toString()
            font.pixelSize: 12

            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    valueNoise.seed = newValue
                    canvas.requestPaint()  // force redraw with new value
                }
            }
        }

        Button {
            id: exportButton
            width: parent.width
            height: 20
            font.pixelSize: 12
            anchors {
                top: seedField.bottom
                topMargin: 20
                right: parent.right
                left: parent.left
                rightMargin: 10
                leftMargin: 10
            }
            contentItem: Text {
                text: "Export"
                font: exportButton.font
                color: 'black'
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
            }
            background: Rectangle {
                radius: 2
                border.color: '#EDEDED'
                color: 'transparent'
                anchors.fill: parent
            }

            onClicked: valueNoise.exportNoise()
        }
    }
}
