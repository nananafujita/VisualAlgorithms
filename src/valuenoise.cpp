#include "valuenoise.h"

#include <cstdlib>

ValueNoise::ValueNoise(QObject* parent)
{
    srand(m_seed);
    for (int i=0; i<m_period; i++) {
        m_lattice.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }
}

// implement smoothstep to achieve smooth linear interpolation
float ValueNoise::noise1D(float x)
{
    int x0 = static_cast<int>(x);
    //int minX = x0 & (numVertices - 1);
    int minX = x0 % m_period;
    float t = x - x0;
    int maxX = (minX == m_period - 1) ? 0 : minX + 1;
    return lerp(smoothstep(t), minX, maxX);
}

float ValueNoise::noise2D(float x, float y){
    return 0.0;
}

void ValueNoise::setPeriod(int p){
    if (m_period != p) {
        updateLatticePeriod(p);
        m_period = p;
        emit periodChanged();
    }
}

void ValueNoise::updateLatticePeriod(int newPeriod) {
    if (m_period < newPeriod) {
        for (int i=m_period; i<newPeriod; i++) {
            m_lattice.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    } else if (m_period > newPeriod ){
        m_lattice.erase(m_lattice.begin() + newPeriod, m_lattice.end());
    }
}

void ValueNoise::setSeed(int s){
    if (m_seed != s) {
        m_seed = s;
        updateLatticeSeed();
        emit seedChanged();
    }
}

void ValueNoise::updateLatticeSeed() {
    srand(m_seed);
    for (int i=0; i<m_period; i++) {
        m_lattice[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
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
