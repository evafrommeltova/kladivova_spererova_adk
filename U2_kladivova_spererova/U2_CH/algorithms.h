#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QtGui>

struct Angle{
    QPoint p; //Point
    double a; //Angle
    double d; //Distance
};

class Algorithms
{
public:
    Algorithms();
    static int getPointLinePosition(QPoint &q,QPoint &p1,QPoint &p2);
    static double getAngle2Vectors(QPoint &p1,QPoint &p2,QPoint &p3,QPoint &p4);
    static double length2Points(QPoint q, QPoint p){return sqrt( (q.x()-p.x())*(q.x()-p.x())+(q.y()-p.y())*(q.y()-p.y()) );}
    static double getPointLineDistance(QPoint &q, QPoint &p1, QPoint &p2);
    static void rotateByAngle(QPolygon &points, double angle);
    static void rotateByAngle(QLine &points, double angle);
    static QPolygon correctCH(QPolygon &ch);

    static QPolygon jarvisScan(std::vector<QPoint> &points);
    static QPolygon qHull(std::vector<QPoint> &points);
    static void qh(unsigned int s, unsigned int e, std::vector<QPoint> &points, QPolygon &ch);
    static void minimumAreaEnclosingRectangle (QPolygon &ch, QPolygon &rectangle, QLine &direction);
    static QPolygon sweepLine(std::vector<QPoint> &points);
    static QPolygon grahamScan (std::vector<QPoint> &points);

};

#endif // ALGORITHMS_H
