#include "widget.h"
#include "ui_widget.h"
#include "algorithms.h"

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

void Widget::on_clear_clicked()
{
    ui->Canvas->clearCanvas();
}

void Widget::on_drawMode_clicked()
{
    ui->Canvas->setDrawMode();
}

void Widget::on_analyze_clicked()
{
    //Analyze point and polygon position
    QPointF q = ui->Canvas->getPoint();

    //get polygons one by one
    std::vector<int> res;

    //Compute result using point and polygon
    for(unsigned int i = 0; i < ui->Canvas->getPolygon(i).size(); i++)
    {
        QPolygonF pol = ui->Canvas->getPolygon(i);

        //Select method
        int result = 0;
        if (ui->comboBox->currentIndex() == 0)
            result = Algorithms::positionPointPolygonWinding(q, pol);
        else
            result = Algorithms::positionPointPolygonRayCrossing(q, pol);

        res.push_back(result);
        ui->Canvas->setResult(res);

    }
    ui->Canvas->repaint();
}

void Widget::on_importPolygons_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Select file"),
                "/",
                "Text file (*.txt);;All files (*.*)");

    std::string path_utf8 = path.toUtf8().constData();

    QString msg;

    ui->Canvas->importPolygons(path_utf8);
    ui->Canvas->repaint();

}

void Widget::on_generatePolygon_clicked()
{
    bool b = 0;

    //Get window size
    int width = ui -> Canvas -> size().width();
    int height = ui -> Canvas -> size().height();

    ui->Canvas->generatePolygon(ui->n_points->text().toInt(&b), width, height);
    ui->Canvas->repaint();
}
