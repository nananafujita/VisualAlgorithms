#include "valuenoise.h"

#include <cstdlib>

ValueNoise::ValueNoise(QObject* parent)
{
    srand(m_seed);
    for (int i=0; i<m_numVertices; i++) {
        m_lattice.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }
}

// implement smoothstep to achieve smooth linear interpolation
float ValueNoise::noise1D(float x)
{
    int x0 = static_cast<int>(x);
    //int minX = x0 & (numVertices - 1);
    int minX = x0 % m_numVertices;
    float t = x - x0;
    int maxX = (minX == m_numVertices - 1) ? 0 : minX + 1;
    return lerp(smoothstep(t), minX, maxX);
}

void ValueNoise::setNumVertices(int n){
    if (m_numVertices != n) {
        m_numVertices = n;
        emit numVerticesChanged();
    }
}

float ValueNoise::smoothstep(float t)
{
    return t * t * (3 - 2 * t);
}

float ValueNoise::lerp(float t, int minX, int maxX)
{
    return m_lattice[minX] * (1 - t) + m_lattice[maxX] * t;
}

float ValueNoise::noise2D(float x, float y){
    return 0.0;
}
