#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QPointF>
#include <vector>
#include <QPolygonF>
#include <QtGui>
#include <QDebug>

class Algorithms
{
public:

    Algorithms();
    static int getPointLinePosition(QPointF &q,QPointF &p1,QPointF &p2);
    static double getAngle2Vectors(QPointF &p1,QPointF &p2,QPointF &p3,QPointF &p4);
    static double length2Points(QPointF q, QPointF p){return sqrt( (q.x()-p.x())*(q.x()-p.x())+(q.y()-p.y())*(q.y()-p.y()) );}
    static int positionPointPolygonWinding(QPointF &q, QPolygonF &pol);
    static int positionPointPolygonRayCrossing(QPointF &q, QPolygonF &pol);
};

#endif // ALGORITHMS_H
