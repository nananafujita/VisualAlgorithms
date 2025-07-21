import QtQuick

// displays noise based on user input
//   from min X to max X, however many periods fit (s steps per period)
//   e.g. if minX=0, maxX=32, period=16, 2 repeating periods displayed
// loop through the width/height of noise here, and call noise() draw functions
Canvas {
    width: 500
    height: 500

    onPaint: {
        var ctx = getContext("2d")
        ctx.fillStyle = "#FFFFFF"
        ctx.fillRect(0, 0, width, height)

        var p = manager.noise.period
        var s = manager.noise.steps
        var minX = manager.minX
        var maxX = manager.maxX
        var numPoints = (maxX - minX) / p * s

        //--- draw functions
        // x, (y for 2D): i scaled for each step in period
        // canvasX, (Y): i scaled across canvas

        // draw ValueNoise 1D: draw line between each point
        // noise function output: y, value from 0 to 1.0
        if (manager.noiseType === 0) {
            ctx.beginPath()
            for (var i = 0; i < numPoints; i++) {
                var x = i % (s - 1) / (s - 1) * p
                var y = manager.noise.noise1D(x)
                var canvasX = i / numPoints * width
                ctx.lineTo(canvasX, height * 5 / 8 - y * height / 4)
            }
            ctx.lineWidth = 2
            ctx.stroke()
        }
        // draw ValueNoise 2D: fill rectangle at each point
        // noise function output: intensity, value from 0 to 255
        else if (manager.noiseType === 1) {
            for (var i = 0; i < numPoints; i++) {
                for (var j = 0; j < numPoints; j++) {
                    var cellW = width / numPoints
                    var x = i % (s - 1) / (s - 1) * p
                    var y = j % (s - 1) / (s - 1) * p
                    var canvasX = i / numPoints * width
                    var canvasY = j / numPoints * height
                    var intensity = Math.floor(manager.noise.noise2D(x, y) * 255)
                    ctx.fillStyle = 'rgb(' + intensity + ', ' + intensity + ', ' + intensity + ')'
                    ctx.fillRect(canvasX, canvasY, cellW,  cellW)
                }
            }
        }
    }
}
