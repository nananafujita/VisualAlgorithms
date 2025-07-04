#ifndef NOISE_H
#define NOISE_H

#include <QObject>

class Noise : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged)
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(int steps READ steps WRITE setSteps NOTIFY stepsChanged)
public:
    explicit Noise(QObject *parent = nullptr);

    Q_INVOKABLE int period() const { return m_period; }
    Q_INVOKABLE int seed() const { return m_seed; }
    Q_INVOKABLE int steps() const { return m_steps; }
    Q_INVOKABLE virtual void exportNoise() const = 0;

public slots:
    void setPeriod(int period);
    void setSeed(int seed);
    void setSteps(int steps);

signals:
    void periodChanged();
    void seedChanged();
    void stepsChanged();

protected:
    virtual void updateLatticePeriod(int newPeriod) = 0;
    virtual void updateLatticeSeed() = 0;

    float smoothstep(float t) const;
    float lerp(float t, float minX, float maxX) const;

    int m_period;
    int m_seed;
    int m_steps;
};

#endif // NOISE_H
