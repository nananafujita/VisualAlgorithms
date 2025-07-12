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

            var p = manager.noise.period
            var s = manager.noise.steps
            if (manager.noiseType === 0) {
                ctx.beginPath()
                for (var i = 0; i < s; i++) {
                    var x = i / (s - 1) * p
                    var y = manager.noise.noise1D(x)
                    var canvasX = i / (s - 1) * width
                    ctx.lineTo(canvasX, height * 5 / 8 - y * height / 4)
                }
                ctx.lineWidth = 2
                ctx.stroke()
            } else if (manager.noiseType === 1) {
                for (var i = 0; i < s; i++) {
                    for (var j = 0; j < s; j++) {
                        var cellW = width / s
                        var x = i / (s - 1) * p
                        var y = j / (s - 1) * p
                        var canvasX = i / (s - 1) * width
                        var canvasY = j / (s - 1) * height
                        var intensity = Math.floor(manager.noise.noise2D(x, y) * 255)
                        ctx.fillStyle = 'rgb(' + intensity + ', ' + intensity + ', ' + intensity + ')'
                        ctx.fillRect(canvasX, canvasY, cellW,  cellW)
                    }
                }
            }
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

            onCurrentIndexChanged: {
                manager.changeNoiseType(currentIndex);
                canvas.requestPaint();
            }
        }

        //----- x Range start
        Text {
            id: xRangeText
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
            text: "X Range"
            color: '#8B8B8B'
        }

        TextField {
            id: xRangeMin
            background: Rectangle {
                color: '#EDEDED'
                radius: 3
            }
            color: '#000000'
            width: xRangeText.width / 2 - 2
            height: 20
            anchors {
                top: xRangeText.bottom
                left: xRangeText.left
                topMargin: 2
            }
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignRight
            bottomPadding: 0
            topPadding: 0

            text: '0'
            font.pixelSize: 12

            /*
            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    manager.noise.period = newValue
                    canvas.requestPaint()
                }
            }*/
        }
        TextField {
            id: xRangeMax
            background: Rectangle {
                color: '#EDEDED'
                radius: 3
            }
            color: '#000000'
            width: xRangeText.width / 2 - 2
            height: 20
            anchors {
                top: xRangeText.bottom
                right: xRangeText.right
                topMargin: 2
            }
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignRight
            bottomPadding: 0
            topPadding: 0

            text: '10'
            font.pixelSize: 12

            /*
            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    manager.noise.period = newValue
                    canvas.requestPaint()
                }
            }*/
        }
        //----- x Range end
        //----- Period start
        Text {
            id: periodText
            width: parent.width
            font.pixelSize: 10
            anchors {
                top: xRangeMin.bottom
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

            text: manager.noise.period.toString()
            font.pixelSize: 12

            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    manager.noise.period = newValue
                    canvas.requestPaint()
                    text = manager.noise.period.toString()
                }
            }
        }
        //----- Period end
        //----- Seed start
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

            text: manager.noise.seed.toString()
            font.pixelSize: 12

            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    manager.noise.seed = newValue
                    canvas.requestPaint()
                    text = manager.noise.seed.toString()
                }
            }
        }
        //----- Seed end
        //----- Steps start
        Text {
            id: stepsText
            width: parent.width
            font.pixelSize: 10
            anchors {
                top: seedField.bottom
                left: periodText.left
                right: periodText.right
                topMargin: 10
            }
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            text: "Steps"
            color: '#8B8B8B'
        }

        TextField {
            id: stepsField
            background: Rectangle {
                color: '#EDEDED'
                radius: 3
            }
            color: '#000000'
            width: parent.width
            height: 20
            anchors {
                top: stepsText.bottom
                left: stepsText.left
                right: stepsText.right
                topMargin: 2
            }
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignRight
            bottomPadding: 0
            topPadding: 0

            text: manager.noise.steps.toString()
            font.pixelSize: 12

            onEditingFinished: {
                const newValue = parseInt(text)
                if (!isNaN(newValue)) {
                    manager.noise.steps = newValue
                    canvas.requestPaint()
                }
            }
        }
        //----- Steps end
        //----- Export button
        Button {
            id: exportButton
            width: parent.width
            height: 20
            font.pixelSize: 12
            anchors {
                top: stepsField.bottom
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
            onClicked: manager.noise.exportNoise()
        }
    }
}
