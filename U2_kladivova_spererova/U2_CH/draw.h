#ifndef DRAW_H
#define DRAW_H
#include <QWidget>
#include <vector>


class Draw : public QWidget
{
    Q_OBJECT

private:
    std::vector<QPoint> points;
    QPolygon ch;
    QPolygon box;
    QLine direction;

public:
    explicit Draw(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);

    void clearCanvas();
    void clearCH(){ch.clear(); repaint();}
    void clearPoints(){points.clear(); repaint();}

    void setCH(QPolygon &hull){ ch = hull;}
    void setPoints(std::vector<QPoint> points_){points = points_;}
    void setBox(QPolygon box_) {box = box_;}
    void setDirection(QLine direction_){direction = direction_;}
    std::vector<QPoint> getPoints(){return points;}
    QPolygon getConvexHull(){return ch;}

signals:

public slots:
};

#endif // DRAW_H
