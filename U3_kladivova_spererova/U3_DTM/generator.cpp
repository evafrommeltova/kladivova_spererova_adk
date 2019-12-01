#include "generator.h"

Generator::Generator()
{

}


std::vector<QPoint3D> Generator::generateHill()
{
    //Initialization
    std::vector<QPoint3D> random_points;
    QPoint3D random;
    QPoint3D peak;

    //Ellipse parameters
    double a = rand()%300;
    double b = rand()%300;
    int n = rand()%20; //Number of point in particular ellipse

    //Divide the ellipse to angles according to n value
    double fi = (2*M_PI)/(n);

    //Set coordinates to the peak
    peak.setX(rand()%200 + 200);
    peak.setY(rand()%200 + 200);
    peak.setZ(rand()%400 + 300);

    //Create more ellipses with different radius and with different heights (bigger radius, smaller height)
    for(int j = 0;j<4;j++)
    {
        //Generate ellipse with n points
        for(int i = 0;i<n;i++)
        {
            random.setX(peak.x() + a*cos(i*fi));
            random.setY(peak.y() + b*sin(i*fi));
            random.setZ(peak.getZ()-j*20);
            random_points.push_back(random);

        }
        a+=j*50;
        b+=j*50;
    }
    return random_points;
}

std::vector<QPoint3D> Generator::generateValley()
{
    //Initialization
    std::vector<QPoint3D> random_points;
    QPoint3D center;
    QPoint3D p; //line edge point
    QPoint3D p1; //line edge point


    int n = rand()%30; //number of points in one line
    double a = rand()%50;  //length of lines from center point

    //Center lowest point
    center.setX(rand()%200 + 200);
    center.setY(rand()%200 + 200);
    center.setZ(rand()%50);

    //Create more parallel lines with different length from center point (bigger length, bigger height)
    for(int j = 0;j<4;j++)
    {
        //Create two parallel lines of points with the same height
        for(int i = 0;i<n;i++)
        {
            p.setX(center.x()+a);
            p.setY(center.y()+i*20);
            p.setZ(center.getZ()+a);

            random_points.push_back(p);

            p1.setX(center.x()-a);
            p1.setY(center.y()+i*20);
            p1.setZ(center.getZ()+a);

            random_points.push_back(p1);
        }
        a+=j*50;
    }

    return random_points;
}

std::vector<QPoint3D> Generator::generateRidge()
{
     //Initialization
     std::vector<QPoint3D> random_points;
     QPoint3D center;
     QPoint3D p; //line edge point
     QPoint3D p1; //line edge point

     int n = rand()%20; //number of points in one line
     double a = rand()%30; //length of lines from center point

     //Center highest point
     center.setX(rand()%200 + 200);
     center.setY(rand()%200 + 200);
     center.setZ(rand()%50 + 700);

     //Create more parallel lines with different length from center point (bigger length, lower height)
     for(int j = 0;j<4;j++)
     {
         //Create two parallel lines of points with the same height
         for(int i = 0;i<n;i++)
         {
             p.setX(center.x()+a);
             p.setY(center.y()+i*10);
             p.setZ(center.getZ()-a);

             random_points.push_back(p);

             p1.setX(center.x()-a);
             p1.setY(center.y()+i*10);
             p1.setZ(center.getZ()-a);

             random_points.push_back(p1);

         }
         a+=j*50;
     }
     return random_points;
}

std::vector<QPoint3D> Generator::generateSaddle(){

    std::vector<QPoint3D> random_points;
    QPoint3D l, r, u, d; //left, right, up, down peaks of hills
    QPoint3D random;

    //Ellipse parameters
    double a = rand()%300;
    double b = rand()%300;
    int n = rand()%10; //Number of point in particular ellipse

    //Saddle hills and holes
    l.setX(50);
    l.setY(240);
    l.setZ(800);

    r.setX(490);
    r.setY(250);
    r.setZ(800);

    u.setX(260);
    u.setY(60);
    u.setZ(300);

    d.setX(250);
    d.setY(500);
    d.setZ(300);

    random_points.push_back(l);
    random_points.push_back(r);
    random_points.push_back(u);
    random_points.push_back(d);

    double fi = 2*M_PI/10;

    for(int i = 0;i<3;i++)
    {
        //Create the hill
        for (int j = 0; j < n; j++)
        {
            random.setX(l.x()+ i*(rand()%70)*cos(j*fi) + rand()%20);
            random.setY(l.y()+ i*(rand()%70)*sin(j*fi) + rand()%20);
            random.setZ(l.getZ()-i*10);
            random_points.push_back(random);
        }

        //Create the right hill
        for (int j = 0; j < n; j++)
        {
            random.setX(r.x()+ i*(rand()%70)*cos(j*fi) + rand()%20);
            random.setY(r.y()+ i*(rand()%70)*sin(j*fi) + rand()%20);
            random.setZ(r.getZ()-i*10);
            random_points.push_back(random);
        }

        //Create the upper hole
        for (int j = 0; j < n; j++)
        {
            random.setX(u.x() + i*(rand()%70)*cos(j*fi) + rand()%20);
            random.setY(u.y() + i*(rand()%70)*sin(j*fi) + rand()%20);
            random.setZ(u.getZ()+i*10);
            random_points.push_back(random);

        }

        //Create the lower hole
        for (int j = 0; j < n; j++)
        {
            random.setX(d.x() + i*(rand()%70)*cos(j*fi) + rand()%20);
            random.setY(d.y() + i*(rand()%70)*sin(j*fi) + rand()%20);
            random.setZ(d.getZ()+i*10);
            random_points.push_back(random);

        }

        a+=i*50;
        b+=i*50;
    }
    return random_points;
}

std::vector<QPoint3D> Generator::generateGentleRidge(){

    //Initialization
    std::vector<QPoint3D> random_points;
    QPoint3D random;
    QPoint3D peak;

    //Ellipse parameters
    double a = rand()%300;
    double b = rand()%300;
    int n = rand()%10 + 3; //Number of point in particular ellipse

    //Divide the ellipse to angles according to n value (special range of angles)
    double fi = (M_PI/3)/(n);

    //Set coordinates to the peak
    peak.setX(rand()%200 + 50);
    peak.setY(rand()%200 + 50);
    peak.setZ(rand()%400 + 300);

    int k = 1; //Make diferent interval between ellipses

    //Create more ellipses with different radius and with different heights
    for(int j = 0;j<8;j++)
    {
        if (j<4){

            //Generate ellipse with growing interval between them
            for(int i = 0;i<n;i++)
            {
                random.setX(peak.x() + a*cos(i*fi));
                random.setY(peak.y() + b*sin(i*fi));
                random.setZ(peak.getZ()-j*10);
                random_points.push_back(random);

            }
            a+=k*30;
            b+=k*30;
            k++;
        }
        else {

            //Generate ellipse with declining interval between them
            for(int i = 0;i<n;i++)
            {
                random.setX(peak.x() + a*cos(i*fi));
                random.setY(peak.y() + b*sin(i*fi));
                random.setZ(peak.getZ()-j*10);
                random_points.push_back(random);

            }
            a+=k*20;
            b+=k*20;
            k--;
        }
    }
    return random_points;
}

std::vector<QPoint3D> Generator::generateGrid(int grid)
{
    std::vector<QPoint3D> random_points;
    QPoint3D p;


    //Classical grid with regular distance
     for(int j = 0; j < 800; j += grid)
     {
         for(int i = 0;i<800;i += grid)
         {
             p.setX(j);
             p.setY(i);
             p.setZ((i+j)/10);

             random_points.push_back(p);
         }
     }
     return random_points;
}
