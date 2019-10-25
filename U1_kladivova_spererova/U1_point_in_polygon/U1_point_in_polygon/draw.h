#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <QWidget>
#include <QtGui>

class Draw : public QWidget
{
    Q_OBJECT

private:
    bool draw_mode;
    QPointF q; //Point q
    QPolygonF polygon; //Polygon P
    std::vector<QPolygonF> polygons; //Polygon vector
    std::vector<int> result;


public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void clearCanvas();
    void setDrawMode(){draw_mode = !draw_mode;} //Switch, whether to draw a point or nothing
    bool importPolygons(std::string &path);
    void generatePolygon(int n_points);
    void setResult(std::vector<int> res){result = res;}
    QPointF getPoint(){return q;}
    QPolygonF getPolygon(unsigned int index){return polygons.at(index);}
    std::vector<QPolygonF> getPolygons(){return polygons;}

signals:

public slots:
};

#endif // DRAW_H
