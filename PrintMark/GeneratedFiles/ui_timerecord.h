/********************************************************************************
** Form generated from reading UI file 'timerecord.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERECORD_H
#define UI_TIMERECORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeRecord
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTimeEdit *timeEdit;
    QLabel *label_4;
    QTimeEdit *timeEdit_4;
    QLabel *label_2;
    QLabel *label_3;
    QTimeEdit *timeEdit_2;
    QTimeEdit *timeEdit_3;

    void setupUi(QWidget *TimeRecord)
    {
        if (TimeRecord->objectName().isEmpty())
            TimeRecord->setObjectName(QStringLiteral("TimeRecord"));
        TimeRecord->resize(348, 260);
        gridLayout = new QGridLayout(TimeRecord);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(TimeRecord);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        timeEdit = new QTimeEdit(TimeRecord);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setEnabled(false);
        timeEdit->setStyleSheet(QLatin1String("::up-button{width:0px;}\n"
"::down-button{width:0px;}\n"
"QTimeEdit{font: 32pt \"DigifaceWide\";border-width:1px;border-style: inset;border-color: darkgray;color:rgb(160, 45, 0);}\n"
""));
        timeEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        timeEdit->setReadOnly(true);

        gridLayout->addWidget(timeEdit, 0, 1, 1, 1);

        label_4 = new QLabel(TimeRecord);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        timeEdit_4 = new QTimeEdit(TimeRecord);
        timeEdit_4->setObjectName(QStringLiteral("timeEdit_4"));
        timeEdit_4->setEnabled(false);
        timeEdit_4->setStyleSheet(QLatin1String("::up-button{width:0px;}\n"
"::down-button{width:0px;}\n"
"QTimeEdit{font: 32pt \"DigifaceWide\";border-width:1px;border-style: inset;border-color: darkgray;color:rgb(154, 154, 0);}\n"
"\n"
""));
        timeEdit_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        timeEdit_4->setReadOnly(true);

        gridLayout->addWidget(timeEdit_4, 3, 1, 1, 1);

        label_2 = new QLabel(TimeRecord);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(TimeRecord);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        timeEdit_2 = new QTimeEdit(TimeRecord);
        timeEdit_2->setObjectName(QStringLiteral("timeEdit_2"));
        timeEdit_2->setEnabled(false);
        timeEdit_2->setStyleSheet(QLatin1String("::up-button{width:0px;}\n"
"::down-button{width:0px;}\n"
"QTimeEdit{font: 32pt \"DigifaceWide\";border-width:1px;border-style: inset;border-color: darkgray;color:darkblue;}\n"
""));
        timeEdit_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        timeEdit_2->setReadOnly(true);

        gridLayout->addWidget(timeEdit_2, 1, 1, 1, 1);

        timeEdit_3 = new QTimeEdit(TimeRecord);
        timeEdit_3->setObjectName(QStringLiteral("timeEdit_3"));
        timeEdit_3->setEnabled(false);
        timeEdit_3->setStyleSheet(QLatin1String("::up-button{width:0px;}\n"
"::down-button{width:0px;}\n"
"QTimeEdit{font: 32pt \"DigifaceWide\";border-width:1px;border-style: inset;border-color: darkgray;color:darkcyan;}\n"
""));
        timeEdit_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        timeEdit_3->setReadOnly(true);

        gridLayout->addWidget(timeEdit_3, 2, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(timeEdit);
        label_4->setBuddy(timeEdit_4);
        label_2->setBuddy(timeEdit_2);
        label_3->setBuddy(timeEdit_3);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(timeEdit, timeEdit_2);
        QWidget::setTabOrder(timeEdit_2, timeEdit_3);
        QWidget::setTabOrder(timeEdit_3, timeEdit_4);

        retranslateUi(TimeRecord);

        QMetaObject::connectSlotsByName(TimeRecord);
    } // setupUi

    void retranslateUi(QWidget *TimeRecord)
    {
        TimeRecord->setWindowTitle(QApplication::translate("TimeRecord", "\346\227\266\351\227\264\350\256\260\345\275\225", nullptr));
        label->setText(QApplication::translate("TimeRecord", "\345\211\215\345\276\205\346\235\277\346\227\266\351\227\264", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("TimeRecord", "mm:ss.z", nullptr));
        label_4->setText(QApplication::translate("TimeRecord", "\350\277\220\350\241\214\346\227\266\351\227\264", nullptr));
        timeEdit_4->setDisplayFormat(QApplication::translate("TimeRecord", "HH:mm:ss", nullptr));
        label_2->setText(QApplication::translate("TimeRecord", "\345\220\216\345\276\205\346\235\277\346\227\266\351\227\264", nullptr));
        label_3->setText(QApplication::translate("TimeRecord", "\345\221\250\346\234\237\346\227\266\351\227\264", nullptr));
        timeEdit_2->setDisplayFormat(QApplication::translate("TimeRecord", "mm:ss.z", nullptr));
        timeEdit_3->setDisplayFormat(QApplication::translate("TimeRecord", "mm:ss.z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeRecord: public Ui_TimeRecord {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERECORD_H
