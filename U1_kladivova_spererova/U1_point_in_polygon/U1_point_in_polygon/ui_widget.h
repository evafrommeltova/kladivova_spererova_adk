/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "draw.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout;
    QPushButton *drawMode;
    QSpacerItem *verticalSpacer_3;
    QPushButton *importPolygons;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;
    QPushButton *analyze;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QLineEdit *n_points;
    QPushButton *generatePolygon;
    QSpacerItem *verticalSpacer_5;
    QPushButton *clear;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1024, 722);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(Widget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        drawMode = new QPushButton(Widget);
        drawMode->setObjectName(QString::fromUtf8("drawMode"));

        verticalLayout->addWidget(drawMode);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        importPolygons = new QPushButton(Widget);
        importPolygons->setObjectName(QString::fromUtf8("importPolygons"));

        verticalLayout->addWidget(importPolygons);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        analyze = new QPushButton(Widget);
        analyze->setObjectName(QString::fromUtf8("analyze"));

        verticalLayout->addWidget(analyze);

        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        n_points = new QLineEdit(Widget);
        n_points->setObjectName(QString::fromUtf8("n_points"));
        n_points->setMaxLength(100);
        n_points->setCursorPosition(1);
        n_points->setAlignment(Qt::AlignCenter);
        n_points->setReadOnly(false);

        verticalLayout->addWidget(n_points);

        generatePolygon = new QPushButton(Widget);
        generatePolygon->setObjectName(QString::fromUtf8("generatePolygon"));

        verticalLayout->addWidget(generatePolygon);

        verticalSpacer_5 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        clear = new QPushButton(Widget);
        clear->setObjectName(QString::fromUtf8("clear"));

        verticalLayout->addWidget(clear);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Analyze point and polygon position", nullptr));
        drawMode->setText(QCoreApplication::translate("Widget", "Draw point/polygon", nullptr));
        importPolygons->setText(QCoreApplication::translate("Widget", "Import polygons", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Select method:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "Winding Algorithm", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "Ray Crossing Algorithm", nullptr));

        analyze->setText(QCoreApplication::translate("Widget", "Analyze", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("Widget", "Select number of vertexes:", nullptr));
        n_points->setText(QCoreApplication::translate("Widget", "4", nullptr));
        generatePolygon->setText(QCoreApplication::translate("Widget", "Generate nonconvex polygon", nullptr));
        clear->setText(QCoreApplication::translate("Widget", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
