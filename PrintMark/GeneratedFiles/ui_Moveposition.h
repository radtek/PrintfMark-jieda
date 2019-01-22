/********************************************************************************
** Form generated from reading UI file 'Moveposition.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVEPOSITION_H
#define UI_MOVEPOSITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Moveposition
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;

    void setupUi(QWidget *Moveposition)
    {
        if (Moveposition->objectName().isEmpty())
            Moveposition->setObjectName(QStringLiteral("Moveposition"));
        Moveposition->resize(385, 113);
        gridLayout = new QGridLayout(Moveposition);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Moveposition);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(Moveposition);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        pushButton = new QPushButton(Moveposition);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        label_2 = new QLabel(Moveposition);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(Moveposition);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(Moveposition);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        label_3 = new QLabel(Moveposition);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(Moveposition);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);


        retranslateUi(Moveposition);

        QMetaObject::connectSlotsByName(Moveposition);
    } // setupUi

    void retranslateUi(QWidget *Moveposition)
    {
        Moveposition->setWindowTitle(QApplication::translate("Moveposition", "Moveposition", nullptr));
        label->setText(QApplication::translate("Moveposition", "X\345\201\217\347\247\273", nullptr));
        pushButton->setText(QApplication::translate("Moveposition", "\347\224\237\346\210\220\346\225\260\346\215\256", nullptr));
        label_2->setText(QApplication::translate("Moveposition", "Y\345\201\217\347\247\273", nullptr));
        pushButton_2->setText(QApplication::translate("Moveposition", "\345\205\263\351\227\255", nullptr));
        label_3->setText(QApplication::translate("Moveposition", "U\345\201\217\347\247\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Moveposition: public Ui_Moveposition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVEPOSITION_H
