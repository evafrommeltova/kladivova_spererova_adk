#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <fstream>
#include "qpointfb.h"
#include "edge.h"

class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPointFB> a,b;
    std::vector<Edge> result;
    bool ab;

public:
    explicit Draw(QWidget *parent = nullptr);
    void changePolygon(){ab = !ab;}

    void setA (std::vector<QPointFB> &a_){a = a_;}
    void setB (std::vector<QPointFB> &b_){b = b_;}
    void setRes (std::vector<Edge> result_){result = result_;}

    std::vector<QPointFB> getA(){return a;}
    std::vector<QPointFB> getB(){return b;}
    std::vector<Edge> getRes(){return result;}

    void clearResults() {result.clear();}
    void clearAll() {result.clear(); a.clear(); b.clear();}

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawPolygon(QPainter &painter, std::vector<QPointFB> &polygon);
    static void importPolygons(std::string &path, std::vector<QPointFB> &A, std::vector<QPointFB> &B,  QSizeF &canvas_size);

signals:

public slots:
};

#endif // DRAW_H
