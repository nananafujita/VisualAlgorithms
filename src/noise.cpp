#include "noise.h"

Noise::Noise(QObject *parent)
    : QObject{parent}, m_seed(2025), m_period(256), m_steps(500)
{}

void Noise::setPeriod(int period)
{
    if (m_period != period) {
        updateLatticePeriod(period);
        m_period = period;
        emit periodChanged();
    }
}

void Noise::setSeed(int seed)
{
    if (m_seed != seed) {
        m_seed = seed;
        updateLatticeSeed();
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

float Noise::smoothstep(float t) const
{
    return t * t * (3 - 2 * t);
}

float Noise::lerp(float t, float a, float b) const
{
    return a * (1 - t) + b * t;
}
