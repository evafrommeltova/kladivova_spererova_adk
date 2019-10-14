#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QObject>
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

private slots:
    void on_clear_clicked();

    void on_drawMode_clicked();

    void on_analyze_clicked();

    void on_importPolygons_clicked();

    void on_generatePolygon_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
