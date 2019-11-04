#include "generator.h"
#include<cmath>
#include <QMessageBox>

Generator::Generator()
{

}

std::vector<QPoint> Generator::generateCircle(int n)
{
    std::vector<QPoint> random_points;

    if(n<3){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 3 points! ");
        msgBox.exec();
        return random_points;
    }

    //Generate center point
    QPoint center(rand()%400+200,rand()%400+150);

    //Generate radius
    double radius = rand()%200;
    double fi = (2*M_PI)/n;
    QPoint q;

    //Generate points of circle
    for(int i = 0; i < n; i++)
    {
        q.setX(center.x() + static_cast<int>(radius*cos(i*fi)));
        q.setY(center.y() + static_cast<int>(radius*sin(i*fi)));
        random_points.push_back(q);
    }
    return random_points;
}

std::vector<QPoint> Generator::generateEllipse(int n)
{
    std::vector<QPoint> random_points;

    if(n<3){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 3 points! ");
        msgBox.exec();
        return random_points;
    }

    //Generate center point
    QPoint center(rand()%400+200,rand()%400+150);

    //Generate length of axis
    double a = rand()%200;
    double b = rand()%200;
    double fi = (2*M_PI)/n;
    QPoint q;

    //Generate points of ellipse
    for(int i = 0; i < n; i++)
    {
        q.setX(center.x() + static_cast<int>(a*cos(i*fi)));
        q.setY(center.y() + static_cast<int>(b*sin(i*fi)));
        random_points.push_back(q);
    }
    return random_points;
}

std::vector<QPoint> Generator::generateSquare(int n)
{
    std::vector<QPoint> random_points;

    if(n<4){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 4 points! ");
        msgBox.exec();
        return random_points;
    }

    if(!(n%4==0)){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be divisible by 4 to make a square. This is the reason why the input was automatically reduced to appropriate number");
        msgBox.exec();
    }

    //Generate left upper corner
    QPoint q(rand()%100+150,rand()%100+100);
    double length = rand()%400;

    //Generate the rest of corners
    QPoint q1(q.x()+static_cast<int>(length),q.y());
    QPoint q2(q.x()+static_cast<int>(length),q.y()+static_cast<int>(length));
    QPoint q3(q.x(),static_cast<int>(q.y()+length));
    random_points.push_back(q);
    random_points.push_back(q1);
    random_points.push_back(q2);
    random_points.push_back(q3);

    //Count small distances between points and add points to vector
    double length_small = length/(n/4);
    for(int i = 0; i < n/4; i++)
    {
        random_points.push_back(QPoint(q1.x()-(static_cast<int>(i*length_small)),q1.y()));
        random_points.push_back(QPoint(q2.x(),q2.y()-static_cast<int>(i*length_small)));
        random_points.push_back(QPoint(q3.x()+(static_cast<int>(i*length_small)),q3.y()));
        random_points.push_back(QPoint(q.x(),q.y()+static_cast<int>(i*length_small)));
    }
    return random_points;
}

std::vector<QPoint> Generator::generateStarShape(int n)
{
    std::vector<QPoint> random_points;

    if(n<6){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 6 points! ");
        msgBox.exec();
        return random_points;
    }

    //Generate center point
    QPoint center(rand()%400+200,rand()%400+150);

    //Generate two different radiuses
    double a = rand()%200;
    double b = rand()%200;

    n/=2;
    double fi = (2*M_PI)/n;
    QPoint q;

    //Generate points of star-shaped polygon
    for(int i = 0;i<n;i++)
    {

        q.setX(center.x() + static_cast<int>(a*cos(i*fi)));
        q.setY(center.y() + static_cast<int>(a*sin(i*fi)));
        random_points.push_back(q);

        q.setX(center.x() + static_cast<int>(b*cos(i*fi+fi/2)));
        q.setY(center.y() + static_cast<int>(b*sin(i*fi+fi/2)));
        random_points.push_back(q);
    }
    return random_points;
}

std::vector<QPoint> Generator::generateRandomPoints(int n)
{
     std::vector<QPoint> random_points;
     QPoint p;

     //Generate random points
     for(int i = 0;i<n;i++)
     {
         p.setX(rand()%600+100);
         p.setY(rand()%600+50);
         random_points.push_back(p);
     }
     return random_points;
}
std::vector<QPoint> Generator::generateGrid(int n)
{
    std::vector<QPoint> random_points;

    if(n<4){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be at least 4 points to make a grid!");
        msgBox.exec();
        return random_points;
    }

    int m = static_cast<int>(sqrt(n));
    if((n-m*m)!=0){
        QMessageBox msgBox;
        msgBox.setText("Warning: The input has to be reduced to make regular grid.");
        msgBox.exec();
    }

     //Generate length between two neighbouring points
     double length_x = rand()%100;
     double length_y = rand()%100;

     //Size of grid
     int size = static_cast<int>(sqrt(n));

     //Set first point (upper left point)
     random_points.push_back(QPoint(10,10));

     //Generate points of grid
     for(int i = 0; i < size; i++)
     {
         for(int j = 0; j < size; j++)
         {
             random_points.push_back(QPoint(random_points[0].x() + i*length_x, random_points[0].y() + j*length_y));
         }
     }
     return random_points;
}


