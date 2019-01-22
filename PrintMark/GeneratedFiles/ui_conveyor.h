/********************************************************************************
** Form generated from reading UI file 'conveyor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVEYOR_H
#define UI_CONVEYOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Conveyor
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_18;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_7;
    QLabel *label_19;
    QSpinBox *spinBox_8;
    QSpinBox *spinBox_9;
    QLabel *label_12;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_21;
    QSpinBox *spinBox;
    QLabel *label_20;
    QSpinBox *spinBox_10;
    QSpinBox *spinBox_11;
    QSpinBox *spinBox_12;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QWidget *Conveyor)
    {
        if (Conveyor->objectName().isEmpty())
            Conveyor->setObjectName(QStringLiteral("Conveyor"));
        Conveyor->resize(454, 279);
        gridLayout_2 = new QGridLayout(Conveyor);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(Conveyor);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        toolButton_3 = new QToolButton(groupBox_2);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/ccw_b.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon);
        toolButton_3->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(groupBox_2);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/cw_b.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon1);
        toolButton_4->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(toolButton_4);


        gridLayout_2->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_6 = new QGroupBox(Conveyor);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        toolButton_7 = new QToolButton(groupBox_6);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));
        toolButton_7->setIcon(icon);
        toolButton_7->setIconSize(QSize(32, 32));

        horizontalLayout_4->addWidget(toolButton_7);

        toolButton_8 = new QToolButton(groupBox_6);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));
        toolButton_8->setIcon(icon1);
        toolButton_8->setIconSize(QSize(32, 32));

        horizontalLayout_4->addWidget(toolButton_8);


        gridLayout_2->addWidget(groupBox_6, 0, 2, 1, 1);

        groupBox_3 = new QGroupBox(Conveyor);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        toolButton_5 = new QToolButton(groupBox_3);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/narrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon2);
        toolButton_5->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(toolButton_5);

        toolButton_6 = new QToolButton(groupBox_3);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/wider.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_6->setIcon(icon3);
        toolButton_6->setIconSize(QSize(32, 32));

        horizontalLayout_3->addWidget(toolButton_6);


        gridLayout_2->addWidget(groupBox_3, 0, 3, 1, 1);

        groupBox = new QGroupBox(Conveyor);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setIcon(icon1);
        toolButton_2->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(toolButton_2);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(Conveyor);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        spinBox_2 = new QSpinBox(groupBox_5);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_2->setMinimum(100);
        spinBox_2->setMaximum(400000);
        spinBox_2->setSingleStep(100);
        spinBox_2->setValue(5000);

        gridLayout_3->addWidget(spinBox_2, 1, 2, 1, 1);

        spinBox_3 = new QSpinBox(groupBox_5);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_3->setMaximum(2000);
        spinBox_3->setSingleStep(10);
        spinBox_3->setValue(500);

        gridLayout_3->addWidget(spinBox_3, 1, 3, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_3->addWidget(label_18, 2, 0, 1, 1);

        spinBox_5 = new QSpinBox(groupBox_5);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_5->setMinimum(1000);
        spinBox_5->setMaximum(400000);
        spinBox_5->setSingleStep(100);
        spinBox_5->setValue(5000);

        gridLayout_3->addWidget(spinBox_5, 2, 2, 1, 1);

        spinBox_4 = new QSpinBox(groupBox_5);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_4->setMinimum(100);
        spinBox_4->setMaximum(400000);
        spinBox_4->setSingleStep(100);
        spinBox_4->setValue(1000);

        gridLayout_3->addWidget(spinBox_4, 2, 1, 1, 1);

        spinBox_6 = new QSpinBox(groupBox_5);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_6->setMaximum(2000);
        spinBox_6->setSingleStep(10);
        spinBox_6->setValue(500);

        gridLayout_3->addWidget(spinBox_6, 2, 3, 1, 1);

        spinBox_7 = new QSpinBox(groupBox_5);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));
        spinBox_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_7->setMinimum(100);
        spinBox_7->setMaximum(400000);
        spinBox_7->setSingleStep(100);
        spinBox_7->setValue(1000);

        gridLayout_3->addWidget(spinBox_7, 3, 1, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_3->addWidget(label_19, 3, 0, 1, 1);

        spinBox_8 = new QSpinBox(groupBox_5);
        spinBox_8->setObjectName(QStringLiteral("spinBox_8"));
        spinBox_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_8->setMinimum(1000);
        spinBox_8->setMaximum(400000);
        spinBox_8->setSingleStep(100);
        spinBox_8->setValue(5000);

        gridLayout_3->addWidget(spinBox_8, 3, 2, 1, 1);

        spinBox_9 = new QSpinBox(groupBox_5);
        spinBox_9->setObjectName(QStringLiteral("spinBox_9"));
        spinBox_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_9->setMaximum(2000);
        spinBox_9->setSingleStep(10);
        spinBox_9->setValue(500);

        gridLayout_3->addWidget(spinBox_9, 3, 3, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_12, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_15, 0, 2, 1, 1);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_16, 0, 3, 1, 1);

        label_21 = new QLabel(groupBox_5);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_3->addWidget(label_21, 1, 0, 1, 1);

        spinBox = new QSpinBox(groupBox_5);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox->setMinimum(100);
        spinBox->setMaximum(400000);
        spinBox->setSingleStep(100);
        spinBox->setValue(1000);

        gridLayout_3->addWidget(spinBox, 1, 1, 1, 1);

        label_20 = new QLabel(groupBox_5);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 4, 0, 1, 1);

        spinBox_10 = new QSpinBox(groupBox_5);
        spinBox_10->setObjectName(QStringLiteral("spinBox_10"));
        spinBox_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_10->setMinimum(100);
        spinBox_10->setMaximum(400000);
        spinBox_10->setSingleStep(100);
        spinBox_10->setValue(1000);

        gridLayout_3->addWidget(spinBox_10, 4, 1, 1, 1);

        spinBox_11 = new QSpinBox(groupBox_5);
        spinBox_11->setObjectName(QStringLiteral("spinBox_11"));
        spinBox_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_11->setMinimum(1000);
        spinBox_11->setMaximum(400000);
        spinBox_11->setSingleStep(100);
        spinBox_11->setValue(5000);

        gridLayout_3->addWidget(spinBox_11, 4, 2, 1, 1);

        spinBox_12 = new QSpinBox(groupBox_5);
        spinBox_12->setObjectName(QStringLiteral("spinBox_12"));
        spinBox_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_12->setMaximum(2000);
        spinBox_12->setSingleStep(10);
        spinBox_12->setValue(500);

        gridLayout_3->addWidget(spinBox_12, 4, 3, 1, 1);

        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);
        gridLayout_3->setColumnStretch(3, 1);

        gridLayout_2->addWidget(groupBox_5, 1, 0, 1, 4);

        pushButton = new QPushButton(Conveyor);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 3, 0, 1, 1);

        label_2 = new QLabel(Conveyor);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 3, 1, 1, 1);


        retranslateUi(Conveyor);

        QMetaObject::connectSlotsByName(Conveyor);
    } // setupUi

    void retranslateUi(QWidget *Conveyor)
    {
        Conveyor->setWindowTitle(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\246", nullptr));
        groupBox_2->setTitle(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2462", nullptr));
        groupBox_6->setTitle(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2463", nullptr));
        groupBox_3->setTitle(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\246\345\256\275\345\272\246", nullptr));
        groupBox->setTitle(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2461", nullptr));
        groupBox_5->setTitle(QApplication::translate("Conveyor", "\351\200\237\345\272\246", nullptr));
        label_18->setText(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2462", nullptr));
        label_19->setText(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\246\345\256\275\345\272\246", nullptr));
        label_12->setText(QApplication::translate("Conveyor", "\345\210\235\351\200\237\345\272\246", nullptr));
        label_15->setText(QApplication::translate("Conveyor", "\351\200\237\345\272\246", nullptr));
        label_16->setText(QApplication::translate("Conveyor", "\345\212\240\351\200\237\346\227\266\351\227\264", nullptr));
        label_21->setText(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2461", nullptr));
        label_20->setText(QApplication::translate("Conveyor", "\344\274\240\351\200\201\345\270\2463", nullptr));
        pushButton->setText(QApplication::translate("Conveyor", "\350\256\260\345\275\225\345\275\223\345\211\215\344\275\215\347\275\256", nullptr));
        label_2->setText(QApplication::translate("Conveyor", "  *\350\256\260\345\276\227\345\233\236\345\216\237\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Conveyor: public Ui_Conveyor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVEYOR_H
