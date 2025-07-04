#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>
#include "noise.h"

class ValueNoise : public Noise
{
    Q_OBJECT

public:
    ValueNoise(QObject* parent = nullptr);

    Q_INVOKABLE float noise1D(float x) const;
    Q_INVOKABLE float noise2D(float x, float y);

    Q_INVOKABLE void exportNoise() const override;

private:

    std::vector<float> m_lattice;

    void updateLatticeSeed() override;
    void updateLatticePeriod(int newPeriod) override;
};

#endif // VALUENOISE_H
