#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <QObject>

class ValueNoise : public QObject
{
    Q_OBJECT;
    Q_PROPERTY(int numVertices READ numVertices WRITE setNumVertices NOTIFY numVerticesChanged);

public:
    ValueNoise(QObject* parent = nullptr);

    Q_INVOKABLE float noise1D(float x);
    Q_INVOKABLE float noise2D(float x, float y);

    Q_INVOKABLE int numVertices() const { return m_numVertices; }

public slots:
    void setNumVertices(int n);

signals:
    void numVerticesChanged();

private:
    int m_numVertices = 10;
    int m_seed = 2025;

    std::vector<float> m_lattice;

    float smoothstep(float t);
    float lerp(float t, int minX, int maxX);
};

#endif // VALUENOISE_H
