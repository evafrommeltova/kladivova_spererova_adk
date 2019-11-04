#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>


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
    void on_create_CH_clicked();

    void on_quit_clicked();

    void on_clear_canvas_clicked();

    void on_generate_clicked();

    void on_minimum_enclosing_box_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
