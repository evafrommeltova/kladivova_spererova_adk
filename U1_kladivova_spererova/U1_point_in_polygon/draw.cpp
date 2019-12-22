#include <cmath>
#include <QtGui>
#include <QMessageBox>
#include <fstream>
#include <string.h>
#include "draw.h"
#include "sortbyy.h"
#include "sortbyx.h"
#include "sortbyangle.h"
#include "qdebug.h"
#include "algorithms.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    //Initialization mode
    draw_mode = false; // false = point; true = nothing

    //Initialization cursor values
    q.setX(-100);
    q.setY(-100);

}

void Draw::mousePressEvent(QMouseEvent *e)
{
    //Get coordinates od the mouse
    int x = e->x();
    int y = e->y();

    //Add points to polygon
    if (draw_mode)
    {
        //Create new point
        QPointF p(x,y);

        //Add point to the list
        polygon.push_back(p);
    }

    //Set coordinate of q
    else {
       q.setX(x);
       q.setY(y);

    }

    polygons.push_back(polygon);

    repaint();
}

void Draw::paintEvent(QPaintEvent *e)
{
    //Macro
    Q_UNUSED(e)

    //Draw polygons and the point
    QPainter qp(this);

    //Start drawing
    qp.begin(this);

    //Draw polygons
    for(unsigned int i = 0; i < polygons.size(); i++)
    {
        //Current polygon from file
        QPolygonF this_polygon = polygons[i];

        //Draw polygon
        qp.drawPolygon(this_polygon);
    }

    //Draw polygon made by cursor
    QPolygonF qpoly;
    int r = 5;
    for (int i = 0; i < polygon.size(); i++)
    {
        qp.drawEllipse(static_cast<int>(polygon[i].x()) - r/2, static_cast<int>(polygon[i].y()) - r/2, r, r);
        qpoly.append(polygon[i]);
    }

    //Draw polygon
    qp.drawPolygon(qpoly);

    //Add to polygons in order to gain the possibility of emphasizing
    polygons.push_back(qpoly);
    qpoly.clear(); //Clear polygon

    //Set Brush
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::Dense3Pattern);
    QPainterPath path;

    QPolygonF polygon_result;

    // Draw polygon with point inside
    for(unsigned int i = 0; i < result.size(); i++)
    {
        // Emphasize polygon with point q inside
        if(result[i] == 1)
        {
            qDebug() << "Point q is inside this polygon";
            polygon_result << polygons[i];
            qDebug() << polygon_result;
            path.addPolygon(polygon_result);
            qp.fillPath(path, brush);
            qp.drawPolygon(polygon_result);
            polygon_result.clear();

        }
        else
            qDebug() << "Point q is outside this polygon";
            qDebug() << polygon_result;
    }

    //Draw point q
    int r2 = 10;
    qp.drawEllipse(static_cast<int>(q.x()) - r,static_cast<int>(q.y()) - r, r2, r2);

    //Stop drawing
    qp.end();
}

void Draw::clearCanvas()
{
    //Clear the Canvas
    polygon.clear();
    q.setX(-100);
    q.setY(-100);
    polygons.clear();
    repaint();
}

bool Draw::importPolygons(std::string &path)
{
    qDebug() << "Clicked Import polygons";
    polygons.clear(); //Delete already opened polygons

    //Input variables for import
    int n;                                  //Number of vertex in polygon
    double x;
    double y;
    QPolygonF polygon;

    std::ifstream myfile(path);

    if(myfile.is_open())
    {
        qDebug() << "File is open";

        //Read file line by line
        while(myfile >> n >> x >> y)
        {
            if(n == 1)
            {
               //If polygon not empty, push back polygon to vector polygons
               if(polygon.empty() == FALSE)
               {
                   polygons.push_back(polygon);
               }

               //Clear whole polygon
               polygon.clear();

               //Add first point to polygon
               polygon << QPointF(x, y);
            }
            else
            {
                //Add point to polygon
                polygon << QPointF(x, y);
            }
        }

        polygons.push_back(polygon); //Save last polygon to vector polygons
        polygon.clear(); //Clear polygon

        //Write to debug all loaded polygons
        for(unsigned int i = 0;i<polygons.size();i++)
        {
            qDebug() << polygons[i];
        }

        //Close imported file
        myfile.close();

        QMessageBox msgBox;
        msgBox.setText("File has been succesfully imported!!");
        msgBox.exec();
        return true;
    }

    QMessageBox msgBox;
    msgBox.setText("Error: File import has failed!!");
    msgBox.exec();
    return false;
}

void Draw::generatePolygon(int n_points, int width, int height)
{
    //Using Graham Scan Algorithm

    clearCanvas();
    polygons.clear(); //Delete already opened polygons

    //Input cannot be a triangle, line or point
    if(n_points < 4){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 4");
        msgBox.exec();
        return;
    }

    //The last point in polygon is center point
    n_points = n_points -1;

    //Generate polygons
     QPolygonF polygon;

    //Generate x and y points
    for(int i = 0; i < n_points; i++)
    {
        QPointF point;
        point.setX(rand()%width);
        point.setY(rand()%height);
        polygon.push_back(point);
    }

    //Sort by Y in order to find pivot
    std::sort(polygon.begin(), polygon.end(), sortByY());

    std::vector<Angle> angles; //Vector of angles from pivot
    int index = 0;

    //Reduce singulary caused by kolinear points
    double eps = 1.0-6;
    for(int i = 1;i<polygon.size();i++)
    {
        if((polygon[0].y() - polygon[i].y())<eps)
        {
            index++;
        }
    }

    //Pivot with min y and max x
    QPointF q = polygon[index];
    polygon.push_back(q);

    //Find s point on axe x
    std::sort(polygon.begin(), polygon.end(), sortByX());
    QPointF s(polygon[0].x(),q.y());

    //Calculate angles and distance beetwen pivot-axes X and pivot-some points
    Angle point;

    for(int i = 0; i<polygon.size();i++)
    {
        //Set some point to the Angle
        point.p.setX(polygon[i].x());
        point.p.setY(polygon[i].y());

        if(q == polygon[i])
        {
            //Angle = 0
            point.a = 0;
            //Distance = 0
            point.d = Algorithms::length2Points(q,polygon[i]);
        }
        else
        {
            //Angle between axe x and some point (pivot is the vertex)
            point.a = Algorithms::getAngle2Vectors(q,s,q, polygon[i]);
            //Distance from pivot to some point
            point.d = Algorithms::length2Points(q,polygon[i]);
        }

        //Angles and distances from pivot to some point
        angles.push_back(point);
    }

    //Sort points in struct Angle by angle and distance
    std::sort(angles.begin(), angles.end(), sortByAngle());

    //Select point of star shape from sorted points
    double angle_before = 0;
    double distance_before = 0;
    QPolygonF pointsByAngle;

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

    polygons.push_back(pointsByAngle);
    pointsByAngle.clear(); //Clear polygon

    repaint();
}
