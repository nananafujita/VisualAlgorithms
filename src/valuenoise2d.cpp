#include "valuenoise2d.h"
#include <QDebug>

ValueNoise2D::ValueNoise2D(QObject* parent)
    : Noise(parent)
{
    populateLattice();
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
    float lerpx0 = lerp(smoothX, m_lattice[yLo][xLo], m_lattice[yLo][xHi]);
    float lerpx1 = lerp(smoothX, m_lattice[yHi][xLo], m_lattice[yHi][xHi]);

    // lerp over y axis
    return(lerp(smoothY, lerpx0, lerpx1));
}

void ValueNoise2D::exportNoise() const
{

}

void ValueNoise2D::populateLattice()
{
    srand(m_seed);
    for (int i=0; i<m_latticeSize; i++) {
        std::vector<float> v;
        for (int j=0; j<m_period; j++) {
            v.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
        if (i < m_lattice.size()) m_lattice[i] = v;
        else m_lattice.push_back(v);
    }
}
