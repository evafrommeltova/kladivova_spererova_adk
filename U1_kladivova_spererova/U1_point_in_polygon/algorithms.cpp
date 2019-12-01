#include "algorithms.h"
#include <cmath>

Algorithms::Algorithms()
{
}


int Algorithms::getPointLinePosition(QPointF &q,QPointF &p1,QPointF &p2)
{
//Analyze point and line position
//1 point in the left half plane
//0 point in the right half plane
//-2 point on the edge or vertex of polygon

//Check singularity when point q is very near or on the edge of polygon
double tol = 1.0e-1;
double p1p2 = length2Points(p1, p2);
double p1q = length2Points(p1, q);
double p2q = length2Points(p2, q);
if (fabs(p1p2 -(p1q+p2q)) < tol)
   return -2;

//Tolerance
double eps = 1.0e-3;

//Check singularity when point q is very near to vertex
if( fabs(q.x()-p1.x())<eps && fabs(q.y()-p1.y())<eps ){
    return -2;
}
if( fabs(q.x()-p2.x())<eps && fabs(q.y()-p2.y())<eps ){
    return -2;
}

//Vectors
double ux = p2.x() - p1.x();
double uy = p2.y() - p1.y();
double vx = q.x() - p1.x();
double vy = q.y() - p1.y();

//Determinant
double t = ux * vy - uy * vx;

//Point in the left half plane
if (t>0)
    return 1;

//Point in the right half plane
if (t<0)
    return 0;
else
    return -1;
}

double Algorithms::getAngle2Vectors(QPointF &p1, QPointF &p2, QPointF &p3, QPointF &p4)
{
    // Calculate Vector betwen 2 vectors.
    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();

    double vx = p4.x() - p3.x();
    double vy = p4.y() - p3.y();

    //Norms
    double nu = sqrt(ux * ux + uy * uy);
    double nv = sqrt(vx * vx + vy * vy);

    //Dot product
    double scalar = ux * vx + uy * vy;

    //Angle in radian
    double angle = fabs(acos(scalar/(nu*nv)));
    return angle;
}


int Algorithms::positionPointPolygonWinding(QPointF &q, QPolygonF &pol)
{
    //Analyze Position of the Point and the Polygon
    double wn = 0.0;

    //Tolerance
    double eps = 1.0e-3;

    //Size of polygon
    int n = pol.size();

    //Browse all points of polygon
    for (int i = 0; i < n; i++){

        //Get orientation of the point and the polygon edge
        int orient = getPointLinePosition(q, pol[i%n], pol[(i+1)%n]);

        //Point q is on the edge, it belongs to polygon
        if(orient==-2)
            return 1;

        //Measure angle
        double omega = getAngle2Vectors(pol[i%n], q, pol[(i+1)%n], q);

        //Point in the left half plane
        if (orient == 1)
            wn += omega;

        //Point in the right half plane
        else
            wn -= omega;
    }

    //Point inside polygon
    if (fabs(fabs(wn) - 2 * M_PI) <= eps)
        return 1;

    //Point q outside P
    if (fabs(wn) < eps)
        return 0;

    //something else???
    else
        return -1;
}

int Algorithms::positionPointPolygonRayCrossing(QPointF &q, QPolygonF &pol)
{
    //Analyze Position of the Point and the Polygon
    int k = 0;

    //Size of polygon
    int n = pol.size();

    //Tolerance
    double eps = 1.0e-3;

    //Reduce first point
    double xir = pol[0].x() - q.x();
    double yir = pol[0].y() - q.y();

    for (int i = 1; i < n+1 ; i++)
    {
        //Reduce coordinates
        double xiir = pol[i%n].x() - q.x();
        double yiir = pol[i%n].y() - q.y();

        //Find out if point lies on the line
        int t = getPointLinePosition(q, pol[i%n], pol[(i+1)%n]);

        //Point q is on the edge, it belongs to polygon
        if(t == -2){
            return 1;
        }

        //Point in the upper half plane
        if (((yir > eps) && (yiir <= eps)) || ((yiir > eps) && (yir <= eps)) )
        {
            // Compute intersection
            double xm = (xir * yiir - xiir * yir)/(yir - yiir);

            // Point in the right plane
            if (xm > 0)
                k +=1;
        }

        //Assign coordinates
        yir = yiir;
        xir = xiir;
    }

    //Odd/even amount of intersections
    return k%2;
}







