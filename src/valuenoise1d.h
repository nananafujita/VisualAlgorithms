#ifndef VALUENOISE1D_H
#define VALUENOISE1D_H

#include <QObject>
#include "noise.h"

class ValueNoise1D : public Noise
{
    Q_OBJECT

public:
    ValueNoise1D(QObject* parent = nullptr);

    float noise1D(float x) const override;
    float noise2D(float x, float y) const override;
    Q_INVOKABLE void exportNoise() const override;

private:

};

#endif // VALUENOISE1D_H
