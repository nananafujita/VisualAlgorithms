#include "noise.h"

#include <random>

Noise::Noise(QObject *parent)
    : QObject{parent}, m_seed(2025), m_period(16), m_steps(500)
{
    populateLattice();
}

void Noise::setPeriod(int period)
{
    period = (period != 0) ? std::abs(period) : 1;

    if (period != 0 && m_period != period) {
        m_period = period;
        emit periodChanged();
    }
}

// when seed changes, m_lattice and permTable also must change
void Noise::setSeed(int seed)
{
    if (m_seed != seed) {
        m_seed = seed;
        populateLattice();
        emit seedChanged();
    }
}

void Noise::setSteps(int steps)
{
    steps = (steps != 0) ? std::abs(steps) : 1;
    if (m_steps != steps) {
        m_steps = steps;
        emit stepsChanged();
    }
}

// fills the m_lattice array with random values
// and shuffles m_permTable indices
void Noise::populateLattice()
{
    std::mt19937 gen(m_seed);
    std::uniform_real_distribution<float> distribFloat(0.0, 1.0);
    for (int i=0; i<m_latticeSize; i++) {
        m_permTable[i] = i;
        m_lattice[i] = distribFloat(gen);
    }

    std::uniform_int_distribution<unsigned> distribInt(0, 255);
    for (int i=0; i<m_latticeSize; i++) {
        int r = distribInt(gen);
        std::swap(m_permTable[i], m_permTable[r]);
        m_permTable[i + m_latticeSize] = m_permTable[i];
    }
}
