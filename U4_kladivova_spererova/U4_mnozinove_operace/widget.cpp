#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"
#include "types.h"
#include <QFileDialog>

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


void Widget::on_pushButton_clicked()
{
    ui->Canvas->changePolygon();
}

void Widget::on_pushButton_2_clicked()
{
    //Get those polygons
    std::vector<QPointFB> A = ui->Canvas->getA();
    std::vector<QPointFB> B = ui->Canvas->getB();

    //Perform Boolean operation
    TBooleanOperation operation;
    switch(ui->comboBox->currentIndex())
    {
        case 0: operation = Union; break;
        case 1: operation = Intersect; break;
        case 2: operation = DifferenceAB; break;
        case 3: operation = DifferenceBA;
    }

    std::vector<Edge> result = Algorithms::booleanOperations(A, B, operation);

    //Set results and update
    ui->Canvas->setRes(result);
    repaint();
}

void Widget::on_pushButton_3_clicked()
{
    ui->Canvas->clearResults();
    repaint();
}

void Widget::on_pushButton_4_clicked()
{
    ui->Canvas->clearAll();
    repaint();
}

void Widget::on_pushButton_5_clicked()
{
    ui->Canvas->clearAll();

    std::vector<QPointFB> A, B;

    QSizeF canvas_size = ui->Canvas->size();

    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Select file"),
                "/",
                "Text file (*.txt);;All files (*.*)");

    std::string path_utf8 = path.toUtf8().constData();

    QString msg;


   Draw::importPolygons(path_utf8, A, B, canvas_size);

   ui->Canvas->setA(A);

   ui->Canvas->setB(B);

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
