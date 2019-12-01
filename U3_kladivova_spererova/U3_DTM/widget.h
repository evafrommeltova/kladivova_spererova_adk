#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <fstream>
#include <QtGui>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    double z_min, z_max, dz;

private slots:

    void on_createDelaunay_clicked();

    void on_clearDT_clicked();

    void on_clearPoints_clicked();

    void on_importPolygons_clicked();

    void on_createContours_clicked();

    void on_generateTerrain_clicked();

    void on_Save_clicked();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_editingFinished();



    void on_analyzeDTM_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
