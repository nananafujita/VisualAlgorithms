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

    int xLo = xInt % m_period;
    int xHi = (xLo + 1) % m_period;
    int yLo = yInt % m_period;
    int yHi = (yLo + 1) % m_period;

    float smoothX = smoothstep(tx);
    float smoothY = smoothstep(ty);

    // lerp over x axis
    float lerpx0 = lerp(smoothX, m_lattice[yLo][xLo], m_lattice[yLo][xHi]);
    float lerpx1 = lerp(smoothX, m_lattice[yHi][xLo], m_lattice[yHi][xHi]);

    return(lerp(smoothY, lerpx0, lerpx1));
}

void ValueNoise2D::exportNoise() const
{

}

void ValueNoise2D::populateLattice()
{
    srand(m_seed);
    for (int i=0; i<m_period; i++) {
        std::vector<float> v;
        for (int j=0; j<m_period; j++) {
            v.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
        if (i < m_lattice.size()) m_lattice[i] = v;
        else m_lattice.push_back(v);
    }
}

void ValueNoise2D::updateLatticePeriod(int newPeriod)
{
    if (m_period < newPeriod) {
        for (int i=0; i<m_period; i++) {
            for (int j=m_period; j<newPeriod; j++) {
                m_lattice[i].push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
            }
        }
        for (int i=m_period; i<newPeriod; i++) {
            std::vector<float> v;
            for (int j=0; j<newPeriod; j++) {
                v.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
            }
            m_lattice.push_back(v);
        }
    }
}

