#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>

class ValueNoise : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged);
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged);
    Q_PROPERTY(int steps READ steps WRITE setSteps NOTIFY stepsChanged);

public:
    ValueNoise(QObject* parent = nullptr);

    Q_INVOKABLE float noise1D(float x) const;
    Q_INVOKABLE float noise2D(float x, float y);

    Q_INVOKABLE int period() const { return m_period; }
    Q_INVOKABLE int seed() const { return m_seed; }
    Q_INVOKABLE int steps() const { return m_steps; }
    Q_INVOKABLE void exportNoise() const;

public slots:
    void setPeriod(int p);
    void setSeed(int s);
    void setSteps(int s);

signals:
    void periodChanged();
    void seedChanged();
    void stepsChanged();

private:
    int m_period = 10;
    int m_seed = 2025;
    int m_steps = 200;

    std::vector<float> m_lattice;

    void updateLatticeSeed();
    void updateLatticePeriod(int newPeriod);
    float smoothstep(float t) const;
    float lerp(float t, int minX, int maxX) const;
};

#endif // VALUENOISE_H
