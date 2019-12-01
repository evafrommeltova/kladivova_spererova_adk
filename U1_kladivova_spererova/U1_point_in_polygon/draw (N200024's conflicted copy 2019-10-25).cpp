#include <cmath>
#include <QtGui>
#include <QMessageBox>
#include <fstream>
#include <string.h>
#include "draw.h"
#include "algorithms.h"
#include "qdebug.h"


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

    //Draw imported polygons
    for(unsigned int i = 0; i < polygons.size(); i++)
    {
        //Current polygon from file
        QPolygonF this_polygon = polygons[i];

        //Draw polygon
        qp.drawPolygon(this_polygon);
    }

    QPolygonF polygon_result;

    // set Brush
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::Dense3Pattern);
    QPainterPath path;

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
    int r = 5;
    int r2 = 10;
    qp.drawEllipse(static_cast<int>(q.x()) - r,static_cast<int>(q.y()) - r, r2, r2);

    //Draw all points and polygon
    QPolygonF qpoly;
    for (int i = 0; i < polygon.size(); i++)
    {
        qp.drawEllipse(static_cast<int>(polygon[i].x()) - r/2, static_cast<int>(polygon[i].y()) - r/2, r, r);
        qpoly.append(polygon[i]);
    }

    //Draw polygon
    qp.drawPolygon(qpoly);

    //Stop drawing
    qp.end();

    //Add to polygons in order to gain the possibility of emphasizing
    polygons.push_back(qpoly);
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

        //Close imported file
        myfile.close();

        QMessageBox msgBox;
        msgBox.setText("File has been succesfully imported!");
        msgBox.exec();
        return true;
    }

    QMessageBox msgBox;
    msgBox.setText("Error: File import has failed!!!");
    msgBox.exec();
    return false;
}

void Draw::generatePolygon(int n_points)
{
    clearCanvas();

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
        point.setX(rand()%1000);
        point.setY(rand()%600);
        polygon.push_back(point);
    }

    //Generate center of polygon
    QPointF center;

    //Count sum of polygon coordinates
    double sumaX = 0;
    double sumaY = 0;

    for(int i = 0; i < n_points; i++){
        sumaX = sumaX + polygon.at(i).x();
        sumaY = sumaY + polygon.at(i).y();
    }

    //Count polygon center coordinates
    center.setX(sumaX/n_points);
    center.setY(sumaY/n_points);

    //Sorted polygon
    QPolygonF polygon_sorted;

    // Sort points in polygon by angles
    while(!polygon.empty()){

        int ind_min = 0;
        double angle_min = 360;
        double fixed_angle = 0;

        //Count angle between axis Y and line
        for(int i = 0; i < polygon.size(); i++) {

            //Angle (smernik)
            double angle = atan(fabs((polygon[i].x()-center.x()))/fabs(polygon[i].y()-center.y()));

            //Check the quadrant and fix the angel
            if((polygon[i].x()-center.x())<0 && (polygon[i].y()-center.y())>0){
                fixed_angle = angle;
            }

            if((polygon[i].x()-center.x())<0 && (polygon[i].y()-center.y())<0){
                fixed_angle = 180-angle;
            }

            if((polygon[i].x()-center.x())>0 && (polygon[i].y()-center.y())<0){
                fixed_angle = 180+angle;
            }

            if((polygon[i].x()-center.x())>0 && (polygon[i].y()-center.y())>0){
                fixed_angle = 360-angle;
            }

            //Find the smallest angle so angles would be in clockwise and final polygon would be topologically correct
            if(fixed_angle<angle_min){
                angle_min = angle;
                ind_min = i;
            }
        }

        //Add point with minimum angle to another polygon in order to count with rest points
        polygon_sorted<<(polygon.takeAt(ind_min));
    }

    //Add center point to final polygon
    polygon_sorted<<center;

    polygons.push_back(polygon_sorted);

    qDebug()<<polygons;

    repaint();
}
