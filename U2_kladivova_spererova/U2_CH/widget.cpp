#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "generator.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_create_CH_clicked()
{
    //Create convex hull
    QPolygon ch;
    std::vector<QPoint> points = ui->Canvas->getPoints();

    //Start time
    clock_t s = std::clock();

    //Create CH
    if (ui->comboBox->currentIndex() == 0)
        ch = Algorithms::jarvisScan(points);
    else if (ui->comboBox->currentIndex() == 1)
        ch = Algorithms::qHull(points);
    else if (ui->comboBox->currentIndex() == 2)
        ch = Algorithms::sweepLine(points);
    else
        ch = Algorithms::grahamScan(points);

    //End time
    clock_t e = std::clock();
    clock_t time = e-s;
    ui->time->setText(QString::number(time) + " ms");

    //Draw
    ui->Canvas->setCH(ch);
    repaint();
}

void Widget::on_generate_clicked()
{
    bool b = 0;

    ui->Canvas->clearCanvas();

    std::vector<QPoint> points;
    //Generate
    if (ui->comboBox_2->currentIndex()==0)
        points = Generator::generateCircle(ui->number_of_points->text().toInt(&b));
    else if (ui->comboBox_2->currentIndex()==1)
        points = Generator::generateEllipse(ui->number_of_points->text().toInt(&b));
    else if (ui->comboBox_2->currentIndex()==2)
        points = Generator::generateSquare(ui->number_of_points->text().toInt(&b));
    else if (ui->comboBox_2->currentIndex()==3)
        points = Generator::generateStarShape(ui->number_of_points->text().toInt(&b));
    else if (ui->comboBox_2->currentIndex()==4)
        points = Generator::generateRandomPoints(ui->number_of_points->text().toInt(&b));
    else if (ui->comboBox_2->currentIndex()==5)
        points = Generator::generateGrid(ui->number_of_points->text().toInt(&b));

    ui->Canvas->setPoints(points);
    ui->Canvas->repaint();
}

void Widget::on_minimum_enclosing_box_clicked()
{
    QLine direction;
    QPolygon box;
    QPolygon ch = ui->Canvas->getConvexHull();
    Algorithms::minimumAreaEnclosingRectangle(ch, box, direction);
    ui->Canvas->setBox(box);
    ui->Canvas->setDirection(direction);
    repaint();
}

void Widget::on_quit_clicked()
{
    int result = QMessageBox::warning(this, tr("Warning!"),
                                   tr("Are you sure you want to close this application?"),
                                   QMessageBox::Ok | QMessageBox::Cancel);

    if(result == QMessageBox::Ok){
        close();
    }
}

void Widget::on_clear_canvas_clicked()
{
    ui->Canvas->clearCanvas();
}
