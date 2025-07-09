#ifndef VALUENOISE2D_H
#define VALUENOISE2D_H

#include <QObject>
#include "noise.h"

class ValueNoise2D : public Noise
{
    Q_OBJECT

public:
    ValueNoise2D(QObject* parent = nullptr);

    Q_INVOKABLE float noise2D(float x, float y) const;
    Q_INVOKABLE void exportNoise() const override;

private:
    std::vector<std::vector<float>> m_lattice;

    void populateLattice() override;
    void updateLatticePeriod(int newPeriod) override;
};

#endif // VALUENOISE2D_H
