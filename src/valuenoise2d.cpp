#include "valuenoise2d.h"
#include <QDebug>

ValueNoise2D::ValueNoise2D(QObject* parent)
    : Noise(parent)
{
}

float ValueNoise2D::noise1D(float x) const
{
    qDebug() << "noise1D() being called on ValueNoise2D";
    return 0.0;
}

// returns a float in [0.0, 1.0]
float ValueNoise2D::noise2D(float x, float y) const
{
    int xInt = static_cast<int>(x);
    int yInt = static_cast<int>(y);

    float tx = x - xInt;
    float ty = y - yInt;

    // m_latticeSize = 256, x % 256 = x & 255
    int xLo = xInt & (m_latticeSize - 1);
    int xHi = (xLo + 1) & (m_latticeSize - 1);
    int yLo = yInt & (m_latticeSize - 1);
    int yHi = (yLo + 1) & (m_latticeSize - 1);

    float smoothX = smoothstep(tx);
    float smoothY = smoothstep(ty);

    // lerp over x axis
    float lerpx0 = lerp(smoothX, m_lattice[m_permTable[xLo] + yLo], m_lattice[m_permTable[xHi] + yLo]);
    float lerpx1 = lerp(smoothX, m_lattice[m_permTable[xLo] + yHi], m_lattice[m_permTable[xHi] + yHi]);

    // lerp over y axis
    return(lerp(smoothY, lerpx0, lerpx1));
}

void ValueNoise2D::exportNoise() const
{

}
