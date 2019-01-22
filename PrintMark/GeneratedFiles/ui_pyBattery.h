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

    void setupUi(QWidget *pyBattery)
    {
        if (pyBattery->objectName().isEmpty())
            pyBattery->setObjectName(QStringLiteral("pyBattery"));
        pyBattery->resize(400, 300);
        lineEdit = new QLineEdit(pyBattery);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(90, 110, 221, 41));
        label = new QLabel(pyBattery);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 40, 101, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(18);
        label->setFont(font);
        pushButton = new QPushButton(pyBattery);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 200, 75, 23));

        retranslateUi(pyBattery);
        QObject::connect(pushButton, SIGNAL(clicked()), pyBattery, SLOT(close()));

        QMetaObject::connectSlotsByName(pyBattery);
    } // setupUi

    void retranslateUi(QWidget *pyBattery)
    {
        pyBattery->setWindowTitle(QApplication::translate("pyBattery", "pyBattery", nullptr));
        label->setText(QApplication::translate("pyBattery", "\347\224\265\351\207\217\346\266\210\350\200\227", nullptr));
        pushButton->setText(QApplication::translate("pyBattery", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pyBattery: public Ui_pyBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PYBATTERY_H
