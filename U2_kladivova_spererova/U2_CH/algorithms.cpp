#include "algorithms.h"
#include <cmath>
#include "sortbyy.h"
#include "sortbyx.h"
#include "sortbyangle.h"
#include "ispointidentical.h"

Algorithms::Algorithms()
{

}

int Algorithms::getPointLinePosition(QPoint &q,QPoint &p1,QPoint &p2)
{
    //Analyze point and line position
    //1 point in the left half plane
    //0 point in the right half plane
    //-1 point on the line

    double eps = 1.0e-6;

    double ux = p2.x() - p1.x();
    double uy = p2.y() - p1.y();
    double vx = q.x() - p1.x();
    double vy = q.y() - p1.y();

    //Determinant
    double t = ux * vy - uy * vx;

    //Point in the left half plane
    if (t > eps)
        return 1;

    //Point in the right half plane
    if (t < -eps)
        return 0;

    //Point on the line
    return -1;
}

double Algorithms::getAngle2Vectors(QPoint &p1, QPoint &p2, QPoint &p3, QPoint &p4)
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

    double angle = fabs(acos(scalar/(nu*nv)));
    return angle;
}

double Algorithms::getPointLineDistance(QPoint &q, QPoint &p1, QPoint &p2)
{
    //Calculate point and line distance
    double numerator = q.x()*(p1.y() - p2.y()) + p1.x()*(p2.y() - q.y()) + p2.x()*(q.y() - p1.y());

    double dx = p2.x()-p1.x();
    double dy = p2.y()-p1.y();

    double denominator = sqrt(dx*dx + dy*dy);

    return fabs(numerator)/denominator;
}

QPolygon Algorithms::jarvisScan(std::vector<QPoint> &points)
{
    //Convex hull
    QPolygon ch;
    unsigned int index = 0;

    //Sort points by Y
    std::sort(points.begin(), points.end(), SortbyY());

    //Find pivot with min y and max x
    QPoint q=points[index];

    //Find r
    std::sort(points.begin(), points.end(), SortbyX());
    QPoint r(q.x()-1,q.y());

    //Initialize points pj, pjj
    QPoint pj = q;
    QPoint pjj = r;

    //Add pivot to CH
    ch.push_back(q);

    // Find points of CH
    do
    {
        //Initialization
        double om_max = 0;
        unsigned int i_max = 0;
        double tol = 1.0e-3;

        //Find point of CH = arg max angle(pi, pj, pjj)
        for(unsigned int i = 0; i < points.size(); i++)
        {
            double omega = getAngle2Vectors(pj, pjj, pj, points[i]);

            //Actualize maximum if the difference between max angle and current angle is greater than the tolerance
            if (omega - om_max >= tol)
            {
                om_max = omega;
                i_max = i;
            }

            //Reduce singularity by colinear points
            else if (fabs(omega - om_max)<tol){
                double dist_i = length2Points(pj, points[i]);
                double dist_i_max = length2Points(pj, points[i_max]);

                if(dist_i > dist_i_max){
                    i_max = i;
                    om_max = omega;
                }
            }
        }

        //Add point to the convex hull
        ch.push_back(points[i_max]);

        //Change index
        pjj = pj;
        pj = points[i_max];

    } while (!(pj == q));

    // Correct singularities in CH (duplicity, point on edge of hull)
    correctCH(ch);

    return ch;

}

QPolygon Algorithms::qHull(std::vector<QPoint> &points)
{
    //Convex Hull by quick hull method
    QPolygon ch;
    std::vector<QPoint> upoints, lpoints;

    // Sort by X.
    std::sort(points.begin(), points.end(), SortbyX());
    QPoint q1 = points[0];
    QPoint q3 = points.back();

    //Add q1, q3 to upoints, lpoints
    upoints.push_back(q1);
    upoints.push_back(q3);

    lpoints.push_back(q1);
    lpoints.push_back(q3);

    // Split to upoints / lpoints
    for(unsigned int i=0; i < points.size();i++){

        //Add to the upper part
        if(getPointLinePosition(points[i], q1, q3) == 1)
            upoints.push_back(points[i]);

        //Add to the lower part
        else if (getPointLinePosition(points[i], q1, q3) == 0)
            lpoints.push_back(points[i]);
    }

    //Call recursive function
    ch.push_back(q3);
    qh(1, 0, upoints, ch);
    ch.push_back(q1);
    qh(0, 1, lpoints, ch);

    // Correct singularities in CH (duplicity, point on edge of hull)
    correctCH(ch);

    return ch;
}

void Algorithms::qh(unsigned int s, unsigned int e, std::vector<QPoint> &points, QPolygon &ch){

    //Recursive procedure
    int i_max = -1;
    double d_max = 0;

    // Browse all points
    for (int unsigned i = 2; i < points.size(); i++)
    {
       // Is the point in the right half plane
        if (getPointLinePosition(points[i], points[s], points[e]) == 0)
        {
            double d = getPointLineDistance(points[i], points[s], points[e]);

            //Actualization of d_max
            if(d > d_max){
                d_max = d;
                i_max = static_cast<int>(i);
            }
        }
    }

    //Suitable point has been found
    if(i_max != -1)
    {
        qh(s, static_cast<unsigned int>(i_max), points, ch);
        ch.push_back(points[static_cast<unsigned int>(i_max)]);
        qh(static_cast<unsigned int>(i_max), e, points, ch);
    }

}

QPolygon Algorithms::sweepLine(std::vector<QPoint> &points)
{
    //Increment method, sweep line
    QPolygon ch;

    //Sort points by X
    std::sort(points.begin(),points.end(),SortbyX());

    //Delete duplicit points in sorted data
    std::vector<QPoint> pointsWithoutDuplicit;
    for(unsigned int i =0; i<points.size() - 1; i++){
        if((points[i].x()!=points[i+1].x()) || (points[i].y()!=points[i+1].y())  ){
            pointsWithoutDuplicit.push_back(points[i]);
        }
    }
    pointsWithoutDuplicit.push_back(points[points.size() - 1]);

    points = pointsWithoutDuplicit;

    unsigned int m = points.size();

    //List of predecessors
    std::vector<unsigned int> p(m);

    //List of successors
    std::vector<unsigned int> n(m);

    // Create initial aproximation
    n[0] = 1;
    n[1] = 0;
    p[0] = 1;
    p[1] = 0;

    // Process all points according to x coordinates
    for (unsigned int i = 2; i < m; i++)
    {
        //Point i lies in the upper half plane
        if(points[i].y() > points[i-1].y()){
            //Link i and its predecessor and successor
            p[i] = i-1;
            n[i] = n[i-1];
        }

        //Point i lies in the lower half plane
        else
        {
            //Link i and its predecessor and successor
            p[i] = p[i-1];
            n[i] = i - 1;
        }

        //Link predecessor and successor and i
        p[n[i]] = i;
        n[p[i]] = i;

        //Fix upper tangent
        while (getPointLinePosition(points[n[n[i]]], points[i], points[n[i]]) == 0)
        {
            //Change predecessor and successor
            p[n[n[i]]] = i;
            n[i] = n[n[i]];
        }

        //Fix lower tangent
        while (getPointLinePosition(points[p[p[i]]], points[i], points[p[i]]) == 1)
        {
            //Change predecessor and successor
            n[p[p[i]]] = i;
            p[i] = p[p[i]];
        }
    }

    //Convert successors to ch
    ch.push_back(points[0]);

    //Second point of CH
    unsigned int index = n[0];

    //Repeat until the first point is found
    while(index != 0)
    {
        //Add to the polygon
        ch.push_back(points[index]);

        //Find its successor
        index = n[index];
    }

    // Correct singularities in CH (duplicity, point on edge of hull)
    correctCH(ch);

    return ch;
}

void Algorithms::minimumAreaEnclosingRectangle (QPolygon &ch, QPolygon &rectangle, QLine &direction)
{
    //Center of local system
    QPoint p1(0,0);

    //Point which defines axis x of local system
    QPoint k1;
    k1.setY(0);

    //Initialization
    double min_angle = 0.0;
    int x_min,y_min,x_max,y_max; //Min max coordinates of transformed convex hull
    int x_min_box = 0, y_min_box = 0, x_max_box = 0, y_max_box = 0; //Min max coordinates of enclosing box
    double min_area = std::numeric_limits<double>::max(); //Set min area to very big value

    //Size of convex hull polygon
    int n = ch.size();

    //Number of convex hull points
    int m = n - 1;

    //Main direction of convex hull
    QPolygon ch_transformed;

    //Save sorted polygon after angle transformation
    QPolygon ch_sorted;

       //Compute coordinates od minimum enclosing rectangle
       for(int i = 0; i < m; i++)
       {
            //Define axis +X of local system which has the center in point p1
            double dist = length2Points(ch[i], ch[i+1]);
            k1.setX(static_cast<int>(dist));

            //Count angle between axis x and given edge of convex hull
            double angle = getAngle2Vectors(ch[i], ch[i+1], p1, k1);

            //Transform whole convex hull to local system
            ch_transformed = ch;
            rotateByAngle(ch_transformed, angle);

            //Find minmax coordinates of transformed convex hull (one edge is parallel with axis x)
            ch_sorted = ch_transformed;
            std::sort(ch_sorted.begin(), ch_sorted.end(), SortbyX());
            x_min = ch_sorted[0].x();
            x_max = ch_sorted[m].x();
            std::sort(ch_sorted.begin(), ch_sorted.end(), SortbyY());
            y_min = ch_sorted[0].y();
            y_max = ch_sorted[m].y();

            //Compute minimum area of transformed polygon
            double area = (x_max - x_min) * (y_max - y_min);

            if(area < min_area)
            {
                //Save minmax coordinates of transformed polygon as enclosing bounding box coordinates
                x_min_box = x_min;
                y_min_box = y_min;
                x_max_box = x_max;
                y_max_box = y_max;
                min_area = area;
                min_angle = angle;
            }
       }

       //Points of minimum encosing box
       QPoint p1_box (x_min_box, y_min_box);
       QPoint p2_box (x_max_box, y_min_box);
       QPoint p3_box (x_max_box, y_max_box);
       QPoint p4_box (x_min_box, y_max_box);

       //Make direction of main line in rectangle
       if(p3_box.x() - p1_box.x() > p3_box.y() - p1_box.y())
       {
           direction.setP1(QPoint(p1_box.x(), (p3_box.y() + p1_box.y())/2)); //QPoint(x_min, 0.5*(y_max+y_min))
           direction.setP2(QPoint(p3_box.x(), (p3_box.y() + p1_box.y())/2)); //QPoint(x_max, 0.5*(y_max+y_min))
       }
       else
       {
           direction.setP1(QPoint(((p3_box.x() + p1_box.x())/2), p1_box.y())); //QPoint(0.5*(x_max+x_min), y_min)
           direction.setP2(QPoint(((p3_box.x() + p1_box.x())/2), p3_box.y())); //QPoint(0.5*(x_max+x_min), y_max)
       }

       // Add points to rectangle
       rectangle.push_back(p1_box);
       rectangle.push_back(p2_box);
       rectangle.push_back(p3_box);
       rectangle.push_back(p4_box);

       // transform  direction and rectangle back to global system
       rotateByAngle(rectangle,-min_angle);
       rotateByAngle(direction,-min_angle);
}

QPolygon Algorithms::grahamScan (std::vector<QPoint> &points)
{
    QPolygon ch;
    std::vector<Angle> angles; //Vector of angles from pivot
    unsigned int index = 0;

    //Sort by Y in order to find pivot
    std::sort(points.begin(), points.end(), SortbyY());

    //Reduce singulary caused by kolinear points
    for(unsigned int i = 1;i<points.size();i++)
    {
        if(points[0].y()== points[i].y())
        {
            index++;
        }
    }

    //Pivot with min y and max x
    QPoint q = points[index];
    ch.push_back(q);

    //Find s point on axe x
    std::sort(points.begin(), points.end(), SortbyX());
    QPoint s(points[0].x(),q.y());

    //Calculate angles and distance beetwen pivot-axes X and pivot-some points
    Angle point;

    for(unsigned int i = 0; i<points.size();i++)
    {
        //Set some point to the Angle
        point.p.setX(points[i].x());
        point.p.setY(points[i].y());

        if(q == points[i])
        {
            //Angle = 0
            point.a = 0;
            //Distance = 0
            point.d = length2Points(q,points[i]);
        }
        else
        {
            //Angle between axe x and some point (pivot is the vertex)
            point.a = getAngle2Vectors(q,s,q, points[i]);
            //Distance from pivot to some point
            point.d = length2Points(q,points[i]);
        }

        //Angles and distances from pivot to some point
        angles.push_back(point);
    }

    //Sort points in struct Angle by angle and distance
    std::sort(angles.begin(), angles.end(), SortbyAngle());

    //Select point of star shape from sorted points
    double angle_before = 0;
    double distance_before = 0;
    QPolygon pointsByAngle;

    //Sort points in polygon pointsByAngle by angle and distance from smallest angle to greatest
    angles.push_back(angles[angles.size()]); //Broaden the vector
    pointsByAngle.push_back(angles[0].p); //Point with smallest angle

    for(unsigned int i = 0; i < angles.size(); i++)
    {
        double eps = 1.0e-9;
        if(fabs(angles[i].a - angle_before) < eps)
        {
            if(angles[i].d>distance_before)
            {
                distance_before = angles[i].d;
            }
        }
        else
        {
            angle_before = angles[i].a;
            distance_before = angles[i].d;
            pointsByAngle.push_back(angles[i-1].p);

        }
    }

    //Add point with min angle
    ch.push_back(pointsByAngle[1]);

    for(int i = 2; i < pointsByAngle.size(); i++)
        {
            bool notConvex = true;
            while(notConvex)
            {
                if(getPointLinePosition(ch[ch.size()-1], ch[ch.size()-2], pointsByAngle[i]) == 0)
                    //Remove point of CH from the back
                    ch.pop_back();
                else
                    //not CH
                    notConvex = false;
            }
            ch.push_back(pointsByAngle[i]);
        }

    // Correct singularities in CH (duplicity, point on edge of hull)
    correctCH(ch);

    return ch;
}

void Algorithms::rotateByAngle(QPolygon &points, double angle)
{
    for(int i = 0; i < points.size(); i++)
    {
        QPoint point = points[i];

        //Transform 2D coordinates of point in polygon regarding to axis center
        points[i].setX(static_cast<int>(cos(angle) * point.x() + sin(angle) * point.y()));
        points[i].setY(static_cast<int>(-sin(angle) * point.x() + cos(angle) * point.y()));
    }
}

void Algorithms::rotateByAngle(QLine &points, double angle)
{
    QPoint p1 = points.p1();
    QPoint p2 = points.p2();

    //Transform 2D coordinates of line regarding to axis center
    points.setP1(QPoint(static_cast<int>(cos(angle) * p1.x() + sin(angle) * p1.y()), static_cast<int>(-sin(angle) * p1.x() + cos(angle) * p1.y())));
    points.setP2(QPoint(static_cast<int>(cos(angle) * p2.x() + sin(angle) * p2.y()), static_cast<int>(-sin(angle) * p2.x() + cos(angle) * p2.y())));
}


QPolygon Algorithms::correctCH(QPolygon &ch)
{
    //Erase identical points
    auto unique_end = std::unique(ch.begin(), ch.end(), isPointIdentical());
    ch.erase(unique_end, ch.end());

    //Delete points on the same line
    for(int i=0; i<(ch.size()-2); i++){
        if(getPointLinePosition(ch[i+2],ch[i],ch[i+1])==-1){
            ch.remove(i+1);
            i--;
        }
    }

    return ch;
}


