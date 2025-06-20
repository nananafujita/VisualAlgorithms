import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1280
    height: 960
    visible: true
    title: qsTr("Visual Algorithms")

    Row {
        anchors.fill: parent
        //spacing: 40

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
                    var v = valueNoise.period;
                    var s = valueNoise.steps();
                    for (var i = 0; i < width; i++) {
                        var x = (i / (s - 1)) * v
                        var y = valueNoise.noise1D(x)
                        ctx.lineTo(i, height / 2 - y * height / 2)
                    }
                    ctx.lineWidth = 2
                    ctx.stroke()
                }
            }
        }

        Rectangle {
            width: 200
            height: parent.height
            radius: 2
            color: '#545454'

            anchors {
                top: parent.top
                right: parent.right
            }

            Column {
                anchors {
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }
                width: parent.width
                height: parent.height

                spacing: 10

                RowLayout {
                    id: periodRow
                    spacing: 5

                    Text {
                        text: "period:"
                        color: '#FFFFFF'
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: periodField
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: 80
                        text: valueNoise.period.toString()

                        onEditingFinished: {
                            const newValue = parseInt(text)
                            if (!isNaN(newValue)) {
                                valueNoise.period = newValue
                                canvas.requestPaint()
                            }
                        }
                    }
                }

                RowLayout {
                    id: seedRow
                    spacing: 5

                    Text {
                        text: "seed: "
                        color: '#FFFFFF'
                        horizontalAlignment: Text.AlignLeft
                    }

                    TextField {
                        id: seedField
                        Layout.preferredWidth: 80
                        text: valueNoise.seed.toString()
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
    }
}
