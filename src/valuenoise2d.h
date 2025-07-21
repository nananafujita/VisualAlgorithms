#ifndef VALUENOISE2D_H
#define VALUENOISE2D_H

#include <QObject>
#include "noise.h"

class ValueNoise2D : public Noise
{
    Q_OBJECT

public:
    ValueNoise2D(QObject* parent = nullptr);

    void populateLattice() override;
    float noise1D(float x) const override;
    float noise2D(float x, float y) const override;
    Q_INVOKABLE void exportNoise() const override;

private:
    std::vector<std::vector<float>> m_lattice;
};

#endif // VALUENOISE2D_H
