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
    populateLattice();
}

// implement smoothstep to achieve smooth linear interpolation
float ValueNoise1D::noise1D(float x) const
{
    int xInt = static_cast<int>(x);
    //int minX = x0 & (numVertices - 1);

    float t = x - xInt;

    int minX = xInt % m_period;   // ensures that the noise repeats
    int maxX = (minX == m_period - 1) ? 0 : minX + 1;

    return lerp(smoothstep(t), m_lattice[minX], m_lattice[maxX]);
}

void ValueNoise1D::exportNoise() const
{
    QFile file(QDir::homePath() + "/1DNoise.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    out << "x,y\n";
    for (int i=0; i<m_steps; i++) {
        float x = static_cast<float>(i) / (m_steps - 1) * m_period;
        float y = noise1D(x);
        out << x << "," << y << "\n";
    }
    qDebug() << "Exporting to:" << QFileInfo(file).absoluteFilePath();
}

void ValueNoise1D::populateLattice()
{
    srand(m_seed);
    for (int i=0; i<m_period; i++) {
        m_lattice.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }
}

// add increment values when growing lattice size
void ValueNoise1D::updateLatticePeriod(int newPeriod)
{
    if (m_period < newPeriod) {
        for (int i=m_period; i<newPeriod; i++) {
            m_lattice.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }
}
