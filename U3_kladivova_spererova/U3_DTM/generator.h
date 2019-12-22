#ifndef GENERATOR_H
#define GENERATOR_H
#include "qpoint3d.h"

class Generator
{
public:
    Generator();

    static std::vector<QPoint3D> generateHill(int width, int height);
    static std::vector<QPoint3D> generateValley(int width, int height);
    static std::vector<QPoint3D> generateRidge(int width, int height);
    static std::vector<QPoint3D> generateSaddle(int width, int height);
    static std::vector<QPoint3D> generateGentleRidge(int width, int height);
    static std::vector<QPoint3D> generateGrid( int grid);
};

#endif // GENERATOR_H
