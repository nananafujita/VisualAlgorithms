#ifndef NOISE_H
#define NOISE_H

#include <QObject>

class Noise : public QObject
{
    Q_OBJECT
public:
    explicit Noise(QObject *parent = nullptr);

signals:
};

#endif // NOISE_H
