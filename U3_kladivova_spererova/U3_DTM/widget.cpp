#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "generator.h"
#include "triangle.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    z_min = 0;
    z_max = 1000;
    dz = 5;

    //Set values
    ui->lineEdit->setText(QString::number(dz));
    ui->lineEdit_2->setText(QString::number(z_min));
    ui->lineEdit_3->setText(QString::number(z_max));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_createDelaunay_clicked()
{
    ui->Canvas->clearDT();

    std::vector<QPoint3D> points = ui->Canvas->getPoints();

    unsigned int p_size = points.size();

    if(p_size == 0){
        QMessageBox msgBox;
        msgBox.setText("You need at first to import or generate points!");
        msgBox.exec();
    }
    else {
        std::vector<Edge> dt = Algorithms::DT(points);
        ui->Canvas->setDt(dt);
        repaint();
    }
}

void Widget::on_clearPoints_clicked()
{
    ui->Canvas->clearPoints();
    repaint();
}

void Widget::on_clearDT_clicked()
{
    ui->Canvas->clearPoints();
    ui->Canvas->clearDT();
    repaint();
}

void Widget::on_createContours_clicked()
{
    std::vector<Edge> dt;

    if (ui->Canvas->getDTsize() == 0){

        //Construct Delaunay triangulation
        std::vector<QPoint3D> points = ui->Canvas->getPoints();
        dt = Algorithms::DT(points);
        ui->Canvas->setDt(dt);
    }
    else{

        //Triangulation has been created
        dt = ui->Canvas->getDT();
    }

    std::vector<int> contour_heights;
    std::vector<int> main_contour_heights;

    //Construct contour lines
    std::vector<Edge> contours = Algorithms::createContourLines(dt,  z_min, z_max, dz, contour_heights);
    ui->Canvas->setContours(contours, contour_heights, dz);

    //Construct main contour lines
    std::vector<Edge> mainContours = Algorithms::createContourLines(dt, z_min, z_max, 5*dz, main_contour_heights);
    ui->Canvas->setMainContours(mainContours, main_contour_heights, dz);

    repaint();
}

void Widget::on_importPolygons_clicked()
{
    ui->Canvas->clearDT();

    std::vector<QPoint3D> points;

    QSizeF canvas_size = ui->Canvas->size();

    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Select file"),
                "/",
                "Text file (*.txt);;All files (*.*)");

    std::string path_utf8 = path.toUtf8().constData();

    QString msg;


   Draw::importPolygons(path_utf8, points, canvas_size, z_min, z_max);

   ui->Canvas->setPoints(points);

   ui->Canvas->repaint();
}

void Widget::on_generateTerrain_clicked()
{
    ui->Canvas->clearDT();

    std::vector<QPoint3D> points;

    //Get window size
    int width = ui -> Canvas -> size().width();
    int height = ui -> Canvas -> size().height();

    //Generate terrain shapes
    if (ui->comboBox->currentIndex()==0)
        points = Generator::generateHill(width, height);

    else if (ui->comboBox->currentIndex()==1)
       points = Generator::generateValley(width, height);

    else if (ui->comboBox->currentIndex()==2)
       points = Generator::generateRidge(width, height);

    else if (ui->comboBox->currentIndex()==3)
       points = Generator::generateSaddle(width, height);

    else if (ui->comboBox->currentIndex()==4)
        points = Generator::generateGentleRidge(width, height);

    else if (ui->comboBox->currentIndex()==5)
        points = Generator::generateGrid(100);

    ui->Canvas->setPoints(points);

    ui->Canvas->repaint();
}

void Widget::on_Save_clicked()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                tr("Select file"),
                "/",
                "Image file (*.png);;All files (*.*)");

    ui->Canvas->grab().save(path);

}

void Widget::on_lineEdit_2_editingFinished()
{
    z_min = ui->lineEdit_2->text().toDouble();
}

void Widget::on_lineEdit_3_editingFinished()
{
    z_max = ui->lineEdit_3->text().toDouble();
}

void Widget::on_lineEdit_editingFinished()
{
    dz = ui->lineEdit->text().toDouble();
}

void Widget::on_analyzeDTM_clicked()
{
    std::vector<Edge> dt;

    if (ui->Canvas->getDTsize() == 0){

        //Construct Delaunay triangulation
        std::vector<QPoint3D> points = ui->Canvas->getPoints();
        dt = Algorithms::DT(points);
        ui->Canvas->setDt(dt);
    }
    else{

        //Triangulation has been created
        dt = ui->Canvas->getDT();
    }

    //Initialize boolean variables
    bool slope = FALSE;
    bool aspect = FALSE;
    bool panchromatic = FALSE;
    bool colorful = FALSE;

    //Analyze DTM
    std::vector<Triangle> dtm = Algorithms::analyzeDTM(dt);

    //Set DTM
    ui->Canvas->setDTM(dtm);

    //Show selected analyze
    if (ui->comboBox_2->currentIndex()==0){
        slope = TRUE;
        aspect = FALSE;
    }
    else if (ui->comboBox_2->currentIndex()==1){
        slope = FALSE;
        aspect = TRUE;
    }

    //Show vizualization
    if (ui->comboBox_3->currentIndex()==0){
        panchromatic = TRUE;
        colorful = FALSE;
    }
    else if (ui->comboBox_3->currentIndex()==1){
        panchromatic = FALSE;
        colorful = TRUE;
    }
    ui->Canvas->setAspect(aspect);
    ui->Canvas->setSlope(slope);
    ui->Canvas->setPanchromatic(panchromatic);
    ui->Canvas->setColorful(colorful);

    repaint();
}
