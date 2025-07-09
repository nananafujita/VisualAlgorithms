#include "noise.h"

Noise::Noise(QObject *parent)
    : QObject{parent}, m_seed(2025), m_period(16), m_steps(500)
{}

void Noise::setPeriod(int period)
{
    period = std::abs(period);
    if (period != 0 && m_period != period) {
        updateLatticePeriod(period);
        m_period = period;
        emit periodChanged();
    }
}

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
    if (m_steps != steps) {
        m_steps = steps;
        emit stepsChanged();
    }
}
