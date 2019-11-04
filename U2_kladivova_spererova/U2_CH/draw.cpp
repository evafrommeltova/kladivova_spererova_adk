#include "draw.h"
#include <QtGui>

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

 void Draw::mousePressEvent(QMouseEvent *event)
 {
     //Get coordinates
     int x = event->x();
     int y = event->y();

     //Add to the list
     QPoint q(x, y);
     points.push_back(q);

     //Repaint screen
     repaint();

 }

 void Draw::paintEvent(QPaintEvent *e)
 {
     Q_UNUSED(e)

     QPainter qp(this);
     qp.begin(this);

     //Draw points
     qp.setPen(Qt::black);
     for(unsigned int i = 0; i < points.size(); i++)

     {
         qp.drawEllipse(static_cast<int>(points[i].x()) - 3, static_cast<int>(points[i].y()) - 3, 6, 6);
     }

     //Draw convex hull
     qp.setPen(Qt::magenta);
     qp.drawPolygon(ch);

     //Draw minimum enclosing box
     qp.setPen(Qt::cyan);
     qp.drawPolygon(box);

     //Draw minimum enclosing box direction
     qp.setPen(Qt::blue);
     qp.drawLine(direction);

     qp.end();

     }

 void Draw::clearCanvas()
 {
     //Clear the Canvas
     ch.clear();
     points.clear();
     box.clear();
     direction.setLine(0,0,0,0);

     repaint();
 }
