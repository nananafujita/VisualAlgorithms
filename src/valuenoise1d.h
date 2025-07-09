#ifndef VALUENOISE1D_H
#define VALUENOISE1D_H

#include <QObject>
#include "noise.h"

class ValueNoise1D : public Noise
{
    Q_OBJECT

public:
    ValueNoise1D(QObject* parent = nullptr);

    Q_INVOKABLE float noise1D(float x) const;
    Q_INVOKABLE void exportNoise() const override;

private:
    std::vector<float> m_lattice;

    void populateLattice() override;
    void updateLatticePeriod(int newPeriod) override;
};

#endif // VALUENOISE1D_H
