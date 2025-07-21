#include "valuenoise1d.h"

#include <cstdlib>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

ValueNoise1D::ValueNoise1D(QObject* parent)
    : Noise(parent)
{
}

// implement smoothstep to achieve smooth linear interpolation
// returns value in [0.0, 1.0]
float ValueNoise1D::noise1D(float x) const
{
    int xInt = static_cast<int>(x);

    // ensure that the noise repeats
    // m_latticeSize = 256, x % 256 = x & 255
    int minX = xInt & (m_latticeSize - 1);
    int maxX = (minX == m_period - 1) ? 0 : minX + 1;

    float t = x - xInt;

    return lerp(smoothstep(t), m_lattice[minX], m_lattice[maxX]);
}

// filler function to allow Noise::noise2D() call
float ValueNoise1D::noise2D(float x, float y) const
{
    qDebug() << "nosie2D being called on ValueNoise1D";
    return 0.0;
}

// saves one period of noise to user's home
// Mac: Users/<username>/1DNoise.csv
void ValueNoise1D::exportNoise() const
{
    QFile file(QDir::homePath() + "/1DValueNoise.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << "x,y\n";

    for (int i=0; i<m_steps; i++) {
        float x = static_cast<float>(i) / (m_steps - 1) * m_period;
        float y = noise1D(x);
        out << x << "," << y << "\n";
    }
    qDebug() << "Exported to:" << QFileInfo(file).absoluteFilePath();
}
