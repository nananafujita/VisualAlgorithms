#include "valuenoise.h"

#include <cstdlib>

ValueNoise::ValueNoise(QObject* parent, unsigned int seed)
{
    srand(seed);
    for (int i=0; i<numVertices; i++) {
        lattice[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
}

// implement smoothstep to achieve smooth linear interpolation
float ValueNoise::noise1D(float x)
{
    int x0 = static_cast<int>(x);
    //int minX = x0 & (numVertices - 1);
    int minX = x0 % (int)numVertices;
    float t = x - x0;
    int maxX = (minX == numVertices - 1) ? 0 : minX + 1;
    return lerp(smoothstep(t), minX, maxX);
}

float ValueNoise::smoothstep(float t)
{
    return t * t * (3 - 2 * t);
}

float ValueNoise::lerp(float t, int minX, int maxX)
{
    return lattice[minX] * (1 - t) + lattice[maxX] * t;
}

float ValueNoise::noise2D(float x, float y){
    return 0.0;
}
