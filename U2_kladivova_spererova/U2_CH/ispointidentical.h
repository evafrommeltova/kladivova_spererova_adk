#ifndef ISPOINTIDENTICAL_H
#define ISPOINTIDENTICAL_H
#include <QtGui>

class isPointIdentical
{
public:
    bool operator ()(QPoint &p1, QPoint &p2){

    double eps = 0.001;

    if (fabs(p1.x() - p2.x()) < eps && fabs(p1.y() - p2.y()) < eps)
            return true;
    return false;
    }
};

#endif // ISPOINTIDENTICAL_H
