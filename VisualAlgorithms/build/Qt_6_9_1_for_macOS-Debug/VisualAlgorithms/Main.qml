import QtQuick

Window {
    width: 1280
    height: 960
    visible: true
    title: qsTr("Hello World")

    Canvas {
        id: canvas
        anchors.fill: parent
        width: 900
        height: 900
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, width, height)

            ctx.beginPath()
            var v = valueNoise.getVertices();
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
