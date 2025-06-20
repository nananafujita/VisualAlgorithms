import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Visual Algorithms")
    color: '#404040'

    Row {
        anchors.fill: parent
        //spacing: 40

        Canvas {
            width: 500
            height: 500
            id: canvas

            anchors {
                left: parent.left
                top: parent.top
                margins: 30
            }

            onPaint: {
                var ctx = getContext("2d")
                ctx.fillStyle = "#FFFFFF"
                ctx.fillRect(0, 0, width, height)

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


        Rectangle {
            width: 200
            height: parent.height
            color: '#545454'

            anchors.top: parent.top
            anchors.right: parent.right

            ColumnLayout {
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 10
                    Layout.alignment: AlignTop
                    spacing: 10

                    Text {
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 10
                        Layout.topMargin: 10
                        text: "period"
                        color: '#FFFFFF'
                    }

                    TextField {
                        background: Rectangle {
                            color: '#404040'
                        }
                        color: '#FFFFFF'
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: 50
                        Layout.rightMargin: 10
                        Layout.topMargin: 10
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
                    width: parent.width
                    spacing: 10
                    Layout.topMargin: 10
                    Text {
                        text: "seed"
                        color: '#FFFFFF'
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignRight
                        Layout.leftMargin: 10
                        Layout.topMargin: 10
                    }

                    TextField {
                        background: Rectangle {
                            color: '#404040'
                        }
                        color: '#FFFFFF'
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: 50
                        Layout.rightMargin: 10
                        Layout.topMargin: 10
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
