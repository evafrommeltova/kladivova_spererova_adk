#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <vector>
#include <vector>
#include <fstream>
#include "qpoint3d.h"
#include "edge.h"
#include "triangle.h"

class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint3D> points;
    std::vector<Edge> dt;
    std::vector<Edge> contours;       //List of contours
    std::vector<Edge> mainContours;   //List of main contours
    std::vector<int> main_contour_heights; //List of main contour heights
    std::vector<int> contour_heights; //List of main contour heights
    int main_dz;                             //distance between main contours
    int dz;                             //distance between contours
    std::vector<Triangle> dtm;
    bool slope, aspect;
    bool panchromatic, colorful;

public:
    explicit Draw(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    std::vector<QPoint3D> & getPoints(){return points;}
    void setPoints(std::vector<QPoint3D> &points_){points=points_;}

    std::vector<Edge> & getDT(){return dt;}
    void setDt(std::vector<Edge> &dt_){dt=dt_;}
    unsigned int getDTsize(){return dt.size();}

    std::vector<Edge> & getContours(){return contours;}
    void setContours(std::vector<Edge> &contours_,std::vector<int> &contour_heights_,int dz_);
    std::vector<Edge> & getMainContours(){return mainContours;}
    void setMainContours(std::vector<Edge> &mainContours_, std::vector<int> &main_contour_heights_,int main_dz_);

    void setSlope(bool &slope_){slope = slope_;}//
    void setAspect(bool &aspect_){aspect = aspect_;}//
    void setPanchromatic(bool &panchromatic_){panchromatic = panchromatic_;}//
    void setColorful(bool &colorful_){colorful = colorful_;}//
    void setDTM(std::vector<Triangle> &dtm_){dtm = dtm_;}

    static void importPolygons(std::string &path, std::vector<QPoint3D> &points,  QSizeF &canvas_size, double &min_z, double &max_z); //

    void clearPoints(){points.clear(); }
    void clearDT(){dt.clear(); contours.clear(); mainContours.clear(); dtm.clear();}


signals:

public slots:
};

#endif // DRAW_H
