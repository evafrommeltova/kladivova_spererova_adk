#ifndef SORTBYY_H
#define SORTBYY_H
#include<QtGui>

class sortByY
{
public:
    bool operator()(QPointF &p1, QPointF &p2)
    {
        double eps = 1.0-6;
        return p1.y() < p2.y() || ((p1.y() - p2.y()) < eps && (p1.x() < p2.x()));
    }
};

#endif // SORTBYY_H
