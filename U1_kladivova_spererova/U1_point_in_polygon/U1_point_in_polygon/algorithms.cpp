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
//-1 point on the line

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
if (t<0)
    return 0;

//Point on the line
//distance between point q, a, b
double eps2 = 2.0;
double dist_qp1 = sqrt((vx*vx)+(vy*vy));
double dist_qp2 = sqrt((q.x()-p2.x())*(q.x()-p2.x()) + (q.y()-p2.y())*(q.y()-p2.y()));
double dist_p1p2 = sqrt((ux*ux)+(uy*uy));
double dist = dist_qp1 + dist_qp2;

if((fabs(dist-dist_p1p2))<=eps2){
    return -2;
}

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
    double eps = 1.0e-6;

    //Size of polygon
    int n = pol.size();

    //Browse all points of polygon
    for (int i = 0; i < n; i++){

        // check singularity point effect on the vertex
        if( fabs(q.x()-pol[i%n].x())<eps && fabs(q.y()-pol[i%n].y())<eps ){
            return 1;
        }
        else{
            //Measure angle
            double omega = getAngle2Vectors(pol[i%n], q, pol[(i+1)%n], q);

            //Get orientation of the point and the polygon edge
            int orient = getPointLinePosition(q, pol[i%n], pol[(i+1)%n]);

            // q point on the line
            if(orient==-2)
                return 1;

            //Point in the left half plane
            if (orient == 1)
                wn += omega;

            //Point in the right half plane
            else
                wn -= omega;
           }
    }

    //Point inside polygon
    if (fabs(fabs(wn) - 2 * M_PI) <= eps)
        return 1;

    //Point q outside P
    if (fabs(wn) < eps)
        return 0;

    //something else ???
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
    double eps = 1.0e-6;

    //Reduce first point
    double xir = pol[0].x() - q.x();
    double yir = pol[0].y() - q.y();

    for (int i = 1; i < n+1 ; i++)
    {
        //Reduce coordinates
        double xiir = pol[i%n].x() - q.x();
        double yiir = pol[i%n].y() - q.y();

        //Point q on the polygon vertex
        if((fabs(q.x()-pol[i%n].x()) < eps) && (fabs(q.y()-pol[i%n].y()) < eps)){
            return 1;
        }

        //Find out if point lies on the line
        int t = getPointLinePosition(q, pol[i%n], pol[(i+1)%n]);

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







