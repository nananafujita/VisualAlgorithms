import QtQuick

Canvas {
    width: 500
    height: 500

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
