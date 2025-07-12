#include "noisemanager.h"
#include <QDebug>

NoiseManager::NoiseManager(QObject *parent)
    : QObject{parent}
{
    m_value1D = new ValueNoise1D(this);
    m_value1D->populateLattice();

    m_value2D = new ValueNoise2D(this);
    m_value2D->populateLattice();

    m_currNoise = m_value1D;
    m_currType = 0;
}

void NoiseManager::changeNoiseType(int type)
{
    switch (type)
    {
        case 0:
            m_currNoise = m_value1D;
            break;
        case 1:
            m_currNoise = m_value2D;
            break;
        default:
            qDebug() << "unknown noise type: " << type;
            return;
    }
    m_currType = type;
    emit noiseChanged();
    emit noiseTypeChanged();
}

