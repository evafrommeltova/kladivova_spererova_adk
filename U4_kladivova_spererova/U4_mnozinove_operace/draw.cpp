#include "draw.h"
#include "qpointfb.h"
#include <QtGui>

Draw::Draw(QWidget *parent) : QWidget(parent)
{
    ab = true;
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    QPointFB q(event->x(), event->y());

    if(ab){

        //Add to A
        a.push_back(q);

    } else {

        //Add to B
        b.push_back(q);

    }
    repaint();
}

void Draw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(this);

    //Draw A
    QPen pA(Qt::green, 2, Qt::SolidLine);
    painter.setPen(pA);
    drawPolygon(painter, a);

    //Draw B
    QPen pB(Qt::blue, 2, Qt::SolidLine);
    painter.setPen(pB);
    drawPolygon(painter, b);

    //Draw result
    QPen pE(Qt::red, 3, Qt::SolidLine);
    painter.setPen(pE);
    for(int i = 0; i < result.size(); i++)
    {
        painter.drawLine(result[i].getStart(), result[i].getEnd());
    }
}

void Draw::drawPolygon(QPainter &painter, std::vector<QPointFB> &polygon)
{
    //Draw polygon
    QPolygon polyg;
    for(int i = 0; i < polygon.size(); i++)
    {
        polyg.append(QPoint (polygon[i].x(), polygon[i].y()));
    }

    painter.drawPolygon(polyg);
}

void Draw::importPolygons(std::string &path,std::vector<QPointFB> &A, std::vector<QPointFB> &B,  QSizeF &canvas_size)
{
    int n;
    double x, y;
    QPointFB p;

    //Go through file and load points into poly_pol (storing all polygons)
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();

    std::ifstream myfile(path);
    if(myfile.is_open())
    {
        A.clear();
        B.clear();

        //Read file line by line
        while(myfile >> n >> x >> y)
       {
            //Set min max for Canvas
            if(x < min_x) min_x = x;
            if(x > max_x) max_x = x;
            if(y < min_y) min_y = y;
            if(y > max_y) max_y = y;

           p.setX(x);
           p.setY(y);

           if(n == 1)
           {
              A.push_back(p);
           }
           else
           {
               B.push_back(p);
           }
        }
    myfile.close();

    }

    //Scale points to canvas size
    double h = canvas_size.height() - 100;
    double w = canvas_size.width() - 100;

    double x_coef = w/(max_x-min_x);
    double y_coef = h/(max_y-min_y);

    //Size polygon
    for(unsigned int i = 0; i < A.size(); i++)
    {
        A[i].setX((A[i].x()-min_x)*x_coef);
        A[i].setY((A[i].y()-min_y)*y_coef);
    }
    for(unsigned int i = 0; i < B.size(); i++)
    {
        B[i].setX((B[i].x()-min_x)*x_coef);
        B[i].setY((B[i].y()-min_y)*y_coef);
    }
}
