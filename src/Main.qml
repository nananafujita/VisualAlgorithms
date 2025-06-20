import QtQuick
import QtQuick.Controls

Window {
    width: 1280
    height: 960
    visible: true
    title: qsTr("Visual Algorithms")

    Row {
        anchors.fill: parent
        spacing: 40

        Column {
            Canvas {
                width: 900
                height: 900
                id: canvas

                anchors {
                    left: parent.left
                    top: parent.top
                    margins: 30
                }

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.clearRect(0, 0, width, height)

                    ctx.beginPath()
                    var v = valueNoise.numVertices;
                    for (var i = 0; i < width; i++) {
                        var x = i / (200 - 1) * v
                        var y = valueNoise.noise1D(x)
                        ctx.lineTo(i, height / 2 - y * height / 2)
                    }

                    ctx.lineWidth = 2
                    ctx.stroke()
                }
            }
        }

        Column {
            anchors {
                top: parent.top
                right: parent.right
                margins: 30
            }

            Text {
                text: "numVertices: "
            }
            TextField {
                id: numVerticesInput
                width: 100
                text: valueNoise.numVertices.toString()
                onEditingFinished: {
                    const newValue = parseInt(text)
                    if (!isNaN(newValue)) {
                        valueNoise.numVertices = newValue
                        canvas.requestPaint()  // force redraw with new value
                    }
                }
            }

        }
    }
}
