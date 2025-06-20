#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>

class ValueNoise : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged);

public:
    ValueNoise(QObject* parent = nullptr);

    Q_INVOKABLE float noise1D(float x);
    Q_INVOKABLE float noise2D(float x, float y);

    Q_INVOKABLE int period() const { return m_period; }

public slots:
    void setPeriod(int n);

signals:
    void periodChanged();

private:
    int m_period = 10;
    int m_seed = 2025;

    std::vector<float> m_lattice;

    float smoothstep(float t);
    float lerp(float t, int minX, int maxX);
};

#endif // VALUENOISE_H
