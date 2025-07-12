#ifndef NOISEMANAGER_H
#define NOISEMANAGER_H

#include <QObject>
#include "noise.h"
#include "valuenoise1d.h"
#include "valuenoise2d.h"

class NoiseManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Noise* noise READ noise NOTIFY noiseChanged)
    Q_PROPERTY(int noiseType READ noiseType NOTIFY noiseTypeChanged)
public:
    explicit NoiseManager(QObject *parent = nullptr);

    Q_INVOKABLE Noise* noise() const { return m_currNoise; }
    Q_INVOKABLE int noiseType() const { return m_currType; }
    Q_INVOKABLE void changeNoiseType(int type);

signals:
    void noiseChanged();
    void noiseTypeChanged();

private:
    int m_currType; // 1: Value1D, 2: Value2D
    Noise* m_currNoise;
    ValueNoise1D* m_value1D;
    ValueNoise2D* m_value2D;
};

#endif // NOISEMANAGER_H
