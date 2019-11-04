#ifndef GENERATOR_H
#define GENERATOR_H
#include <QtGui>
#include <QDebug>

class Generator
{
public:
    Generator();
    static std::vector<QPoint> generateCircle(int n);
    static std::vector<QPoint> generateEllipse(int n);
    static std::vector<QPoint> generateSquare(int n);
    static std::vector<QPoint> generateStarShape(int n);
    static std::vector<QPoint> generateRandomPoints(int n);
    static std::vector<QPoint> generateGrid(int n);
};

#endif // GENERATOR_H
