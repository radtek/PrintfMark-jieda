/********************************************************************************
** Form generated from reading UI file 'pyBattery.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PYBATTERY_H
#define UI_PYBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pyBattery
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QLabel *label_2;

    void setupUi(QWidget *pyBattery)
    {
        if (pyBattery->objectName().isEmpty())
            pyBattery->setObjectName(QStringLiteral("pyBattery"));
        pyBattery->resize(394, 318);
        lineEdit = new QLineEdit(pyBattery);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(80, 70, 221, 41));
        label = new QLabel(pyBattery);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 10, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(18);
        label->setFont(font);
        pushButton = new QPushButton(pyBattery);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(300, 270, 75, 23));
        lineEdit_2 = new QLineEdit(pyBattery);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setGeometry(QRect(80, 180, 221, 41));
        label_2 = new QLabel(pyBattery);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 120, 101, 51));
        label_2->setFont(font);

        retranslateUi(pyBattery);
        QObject::connect(pushButton, SIGNAL(clicked()), pyBattery, SLOT(close()));

        QMetaObject::connectSlotsByName(pyBattery);
    } // setupUi

    void retranslateUi(QWidget *pyBattery)
    {
        pyBattery->setWindowTitle(QApplication::translate("pyBattery", "pyBattery", nullptr));
        label->setText(QApplication::translate("pyBattery", "\347\224\265\351\207\217\346\266\210\350\200\227", nullptr));
        pushButton->setText(QApplication::translate("pyBattery", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QApplication::translate("pyBattery", "\345\275\223\345\211\215\346\260\224\345\216\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pyBattery: public Ui_pyBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PYBATTERY_H
