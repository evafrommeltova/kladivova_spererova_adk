#ifndef GENERATOR_H
#define GENERATOR_H
#include "qpoint3d.h"

class Generator
{
public:
    Generator();

    static std::vector<QPoint3D> generateHill();
    static std::vector<QPoint3D> generateValley();
    static std::vector<QPoint3D> generateRidge();
    static std::vector<QPoint3D> generateSaddle();
    static std::vector<QPoint3D> generateGentleRidge();
    static std::vector<QPoint3D> generateGrid(int grid);
};

#endif // GENERATOR_H
