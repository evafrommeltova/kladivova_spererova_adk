#include <QBrush>
#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::setContours(std::vector<Edge> &contours_,std::vector<int> &contour_heights_,int dz_){
    contours = contours_;
    contour_heights = contour_heights_;
    dz = dz_;
}

void Draw::setMainContours(std::vector<Edge> &mainContours_, std::vector<int> &main_contour_heights_,int main_dz_){
    mainContours = mainContours_;
    main_contour_heights = main_contour_heights_;
    main_dz = main_dz_;
}

void Draw::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)

    QPainter painter(this);
    painter.begin(this);
    painter.setPen(Qt::green);

    //Draw points (green)
    for (unsigned int i = 0; i < points.size(); i++)
    {
        painter.drawEllipse(static_cast<int>(points[i].x()) - 5, static_cast<int>(points[i].y()) - 5, 10, 10);
    }

    //Draw Delaunay edges (green)
    for (unsigned int i = 0; i < dt.size(); i++)
    {
        painter.drawLine(dt[i].getStart(), dt[i].getEnd());
    }

    //Draw slope
    if(slope == TRUE)
    {
        for (Triangle t : dtm)
        {
            //Get triangle vertices
            QPoint3D p1 = t.getP1();
            QPoint3D p2 = t.getP2();
            QPoint3D p3 = t.getP3();

            if(panchromatic == TRUE){
                double k = 255.0 / 90;
                int slope = static_cast<int>(255 - t.getSlope() * k);

                //Set panchromatic color brush
                QColor c(slope, slope, slope);
                painter.setBrush(c);
            }

            if(colorful == TRUE){

                int slope = static_cast<int>(t.getSlope());

                //Slope values can be from 0 to 90°
                //Create semi-transparent color palette
                if((slope>=0) && (slope<1)){
                   painter.setBrush(QColor(5, 148, 0, 187)); //Dark green
                }
                else if((slope>=1) && (slope<3)){
                   painter.setBrush(QColor(8, 186, 2, 187));
                }
                else if((slope>=3) && (slope<5)){
                   painter.setBrush(QColor(110, 205, 26, 187));
                }
                else if((slope>=5) && (slope<7)){
                   painter.setBrush(QColor(168, 228, 49, 187));
                }
                else if((slope>=7) && (slope<10)){
                   painter.setBrush(QColor(224, 240, 0, 187));
                }
                else if((slope>=10) && (slope<13)){
                   painter.setBrush(QColor(240, 200, 0, 187));
                }
                else if((slope>=13) && (slope<17)){
                   painter.setBrush(QColor(240, 152, 0, 187));
                }
                else if((slope>=17) && (slope<22)){
                   painter.setBrush(QColor(240, 112, 0, 187));
                }
                else
                   painter.setBrush(QColor(240, 40, 0, 187)); //Dark red
            }

            //Create polygon
            QPolygonF triangle;
            triangle.append(QPointF(p1.x(), p1.y()));
            triangle.append(QPointF(p2.x(), p2.y()));
            triangle.append(QPointF(p3.x(), p3.y()));

            painter.drawPolygon(triangle);

        }
    }

    //Draw aspect
    if(aspect == TRUE)
    {
        for (Triangle t : dtm)
        {
            //Get triangle vertices
            QPoint3D p1 = t.getP1();
            QPoint3D p2 = t.getP2();
            QPoint3D p3 = t.getP3();

            if(panchromatic == TRUE){
                double k = 255.0 / 360;
                int aspect = static_cast<int>(255 - t.getAspect() * k);

                //Set panchromatic color brush
                QColor c(aspect, aspect, aspect);
                painter.setBrush(c);
            }

            if(colorful == TRUE){

                int aspect = static_cast<int>(t.getAspect());

                // Create semi-transparent color palette
                if(((aspect>=0.0) && (aspect<22.5)) || ((aspect>=-22.5) && (aspect<=0.0))){
                    painter.setBrush(QColor(133, 210, 0, 187)); //Light green
                }
                else if((aspect>=22.5) && (aspect<67.5)){
                    painter.setBrush(QColor(0, 168, 17, 187)); //Dark green
                }
                else if((aspect>=67.5) && (aspect<112.5)){
                    painter.setBrush(QColor(0, 22, 168, 187)); //Dark blue
                }
                else if((aspect>=112.5) && (aspect<157.5)){
                   painter.setBrush(QColor(106, 0, 168, 187)); //Purple
                }
                else if(((aspect>=157.5) && (aspect<180.0)) || ((aspect>=-180.0) && (aspect<-157.5)) ){
                    painter.setBrush(QColor(168, 0, 134, 187)); //Red/purple
                }
                else if((aspect>=-157.5) && (aspect<-112.5)){
                    painter.setBrush(QColor(238, 95, 124, 187)); //Pink
                }
                else if((aspect>=-112.5) && (aspect<-67.5)){
                    painter.setBrush(QColor(223, 163, 43, 187)); //Orange
                }
                else if((aspect>=-67.5) && (aspect<-22.5)){
                    painter.setBrush(QColor(255, 255, 44, 187)); //Yellow
                }
            }

            //Create and draw the polygon
            QPolygonF triangle;
            triangle.append(QPointF(p1.x(), p1.y()));
            triangle.append(QPointF(p2.x(), p2.y()));
            triangle.append(QPointF(p3.x(), p3.y()));

            painter.drawPolygon(triangle);
        }
    }

    //Draw contour lines (brown)
    for (unsigned int i = 0; i < contours.size(); i++)
    {
        painter.drawLine(contours[i].getStart(), contours[i].getEnd());
        painter.setPen(QPen(QColor(139,69,19),1));
    }

    //Draw main contour lines (brown,2) and make automatic text description of main contour heights
    for(unsigned int i = 0; i < mainContours.size(); i++)
    {
        painter.drawLine(mainContours[i].getStart(), mainContours[i].getEnd());
        painter.setPen(QPen(QColor(139,69,19),2));

        int h_main = static_cast<int>(main_contour_heights[i]);

        double text_x = (mainContours[i].getStart().x() + mainContours[i].getEnd().x())/2;
        double text_y = (mainContours[i].getStart().y() + mainContours[i].getEnd().y())/2;
        painter.drawText(static_cast<int>(text_x), static_cast<int>(text_y), QString::number(h_main));
    }
    painter.end();
}

void Draw::mousePressEvent(QMouseEvent *event)
{
    //Get coordinates of cursor
    QPoint3D p;
    p.setX(event ->x());
    p.setY(event ->y());

    double random = std::rand() * 40.0/RAND_MAX ;
    p.setZ(random);

    //Add point to the list
    points.push_back(p);

    repaint();
};

void Draw::importPolygons(std::string &path, std::vector<QPoint3D> &points,  QSizeF &canvas_size, double &min_z, double &max_z)
{
    double x, y, z;
    QPoint3D p;

    //Storing all polygons
    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double max_y = std::numeric_limits<double>::min();
    min_z = std::numeric_limits<double>::max();
    max_z = std::numeric_limits<double>::min();


    std::ifstream myfile(path);
    if(myfile.is_open())
    {
        while(myfile >> x >> y >> z)
        {
            p.setX(x);
            p.setY(y);
            p.setZ(z);

            points.push_back(p);

            if(x < min_x) min_x = x;
            if(x > max_x) max_x = x;
            if(y < min_y) min_y = y;
            if(y > max_y) max_y = y;
            if(z < min_z) min_z = z;
            if(z > max_z) max_z = z;
        }

        myfile.close();
    }

        //Scale points to canvas size
        double h = canvas_size.height() - 40;
        double w = canvas_size.width() - 40;

        double x_coef = w/(max_x-min_x);
        double y_coef = h/(max_y-min_y);

        for(unsigned int i = 0; i < points.size(); i++)
        {
            points[i].setX((points[i].x()-min_x)*x_coef);
            points[i].setY((points[i].y()-min_y)*y_coef);
        }
}
