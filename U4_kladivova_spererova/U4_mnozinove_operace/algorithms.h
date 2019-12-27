#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "qpointfb.h"
#include "edge.h"
#include "types.h"
#include <vector>
#include <cmath>

class Algorithms
{
public:
    Algorithms();

    static TPointLinePosition getPointLinePosition(QPointFB &q,QPointFB &p1,QPointFB &p2);
    static double getAngle2Vectors(QPointFB &p1,QPointFB &p2,QPointFB &p3,QPointFB &p4);
    static double length2Points(QPointFB q, QPointFB p){return sqrt( (q.x()-p.x())*(q.x()-p.x())+(q.y()-p.y())*(q.y()-p.y()) );}
    static TPointPolygonPosition positionPointPolygonWinding(QPointFB &q, std::vector<QPointFB> &pol);
    static T2LinePosition get2LinesPosition(QPointFB &p1,QPointFB &p2,QPointFB &p3, QPointFB &p4, QPointFB &pi);
    static std::vector<Edge> booleanOperations(std::vector<QPointFB> &polygonA, std::vector<QPointFB> &polygonB, TBooleanOperation operation);
    static void processIntersection(QPointFB &pi, double &t, std::vector<QPointFB> &polygon, int &i);
    static void computePolygonIntersection(std::vector<QPointFB>&polygonA, std::vector<QPointFB> &polygonB);
    static void setPositionsAB(std::vector<QPointFB> &polygonA, std::vector<QPointFB> &polygonB);
    static void setPositions(std::vector<QPointFB> &polygonA, std::vector<QPointFB> &polygonB);
    static void selectEdges(std::vector<QPointFB> &pol, TPointPolygonPosition position, std::vector<Edge> &edges);
};

#endif // ALGORITHMS_H
