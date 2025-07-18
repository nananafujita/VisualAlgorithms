#ifndef VALUENOISE1D_H
#define VALUENOISE1D_H

#include <QObject>
#include "noise.h"

class ValueNoise1D : public Noise
{
    Q_OBJECT

public:
    ValueNoise1D(QObject* parent = nullptr);

    void populateLattice() override;
    float noise1D(float x) const override;
    float noise2D(float x, float y) const;
    Q_INVOKABLE void exportNoise() const override;

private:
    std::vector<float> m_lattice;
    void updateLatticePeriod(int newPeriod) override;
};

#endif // VALUENOISE1D_H
