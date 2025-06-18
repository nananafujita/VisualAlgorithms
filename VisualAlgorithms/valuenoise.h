#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>

class ValueNoise : public QObject
{
    Q_OBJECT;
public:
    ValueNoise(QObject* parent = nullptr, unsigned int seed = 2025);

    Q_INVOKABLE float noise1D(float x);
    Q_INVOKABLE float noise2D(float x, float y);

    Q_INVOKABLE int getVertices() const {return numVertices;}

private:
    static const int numVertices = 10;
    float lattice[numVertices];

    float smoothstep(float t);
    float lerp(float t, int minX, int maxX);
};

#endif // VALUENOISE_H
