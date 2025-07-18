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
    Q_PROPERTY(int noiseType READ noiseType WRITE setNoiseType NOTIFY noiseTypeChanged)
    Q_PROPERTY(int minX READ minX WRITE setMinX NOTIFY xRangeChanged)
    Q_PROPERTY(int maxX READ maxX WRITE setMaxX NOTIFY xRangeChanged)

public:
    explicit NoiseManager(QObject *parent = nullptr);

    Q_INVOKABLE Noise* noise() const { return m_currNoise; }
    Q_INVOKABLE int noiseType() const { return m_currType; }
    Q_INVOKABLE int minX() const { return m_minX; }
    Q_INVOKABLE int maxX() const { return m_maxX; }

public slots:
    void setNoiseType(int type);
    void setMinX(int x);
    void setMaxX(int x);

signals:
    void noiseChanged();
    void noiseTypeChanged();
    void xRangeChanged();

private:
    int m_currType; // 0: Value1D, 1: Value2D

    // will point to one of the inherited Noise object pointers below
    // draw functions are called on this pointer
    Noise* m_currNoise;
    ValueNoise1D* m_value1D;
    ValueNoise2D* m_value2D;

    // display x limits. default: 0, 10
    int m_minX;
    int m_maxX;
};

#endif // NOISEMANAGER_H
