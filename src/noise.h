#ifndef NOISE_H
#define NOISE_H

#include <QObject>

// pure virtual class for all Noise types
class Noise : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int seed READ seed WRITE setSeed NOTIFY seedChanged)
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(int steps READ steps WRITE setSteps NOTIFY stepsChanged)

public:
    explicit Noise(QObject *parent = nullptr);
    virtual ~Noise() = default;

    // fills the lattice with a float in the range [0.0, 1.0]
    // called by setSeed()
    virtual void populateLattice() = 0;

    Q_INVOKABLE int period() const { return m_period; }
    Q_INVOKABLE int seed() const { return m_seed; }
    Q_INVOKABLE int steps() const { return m_steps; }

    // virtual functions called by NoiseManager's Noise* currNoise
    // 1d and 2d exist here to allow Noise* to call these functions
    Q_INVOKABLE virtual float noise1D(float x) const = 0;
    Q_INVOKABLE virtual float noise2D(float x, float y) const = 0;

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
    // input values from user
    int m_period = 16;
    int m_seed = 2025;
    int m_steps = 500;

    // can not be changed by user
    int m_latticeSize = 256;
};

inline float smoothstep(float t)
{
    return t * t * (3 - 2 * t);
}

inline float lerp(float t, float a, float b)
{
    return a * (1 - t) + b * t;
}


#endif // NOISE_H
