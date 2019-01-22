/********************************************************************************
** Form generated from reading UI file 'sfcwin.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SFCWIN_H
#define UI_SFCWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SfcWin
{
public:
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_5;
    QTextEdit *textEdit;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_3;
    QFrame *line;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpinBox *spinBox;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *SfcWin)
    {
        if (SfcWin->objectName().isEmpty())
            SfcWin->setObjectName(QStringLiteral("SfcWin"));
        SfcWin->resize(461, 371);
        gridLayout_2 = new QGridLayout(SfcWin);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit_5 = new QLineEdit(SfcWin);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 1, 1, 1, 1);

        textEdit = new QTextEdit(SfcWin);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setReadOnly(true);

        gridLayout_2->addWidget(textEdit, 4, 0, 1, 2);

        label_8 = new QLabel(SfcWin);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        lineEdit = new QLineEdit(SfcWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(SfcWin);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(SfcWin);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        groupBox = new QGroupBox(SfcWin);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setCheckable(true);
        groupBox->setChecked(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(false);

        gridLayout->addWidget(lineEdit_3, 6, 0, 1, 3);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 3);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setEnabled(false);

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 10, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(false);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 9, 0, 1, 3, Qt::AlignRight);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 3, Qt::AlignRight);

        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(false);
        spinBox->setMinimum(1);

        gridLayout->addWidget(spinBox, 0, 1, 1, 2);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(false);

        gridLayout->addWidget(lineEdit_2, 4, 0, 1, 3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(false);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        gridLayout->setRowStretch(10, 1);

        gridLayout_2->addWidget(groupBox, 0, 2, 5, 1);

        label_6 = new QLabel(SfcWin);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(SfcWin);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 2, 1, 1, 1);


        retranslateUi(SfcWin);

        QMetaObject::connectSlotsByName(SfcWin);
    } // setupUi

    void retranslateUi(QWidget *SfcWin)
    {
        SfcWin->setWindowTitle(QApplication::translate("SfcWin", "SFC\347\252\227\345\217\243", nullptr));
        label_8->setText(QApplication::translate("SfcWin", "\347\253\231\345\210\245\345\220\215\347\250\261", nullptr));
        label_2->setText(QApplication::translate("SfcWin", "\350\277\224\345\233\236\347\273\223\346\236\234", nullptr));
        label->setText(QApplication::translate("SfcWin", "\345\267\245\345\215\225\345\217\267\347\240\201", nullptr));
        groupBox->setTitle(QApplication::translate("SfcWin", "\346\265\213\350\257\225Web Service", nullptr));
        label_5->setText(QApplication::translate("SfcWin", "\345\260\217\346\235\277\345\217\267\347\240\201", nullptr));
        label_3->setText(QApplication::translate("SfcWin", "\345\260\217\346\235\277\345\217\267\347\240\201\346\225\260\351\207\217", nullptr));
        pushButton_2->setText(QApplication::translate("SfcWin", "FinishPrintInfo", nullptr));
        pushButton->setText(QApplication::translate("SfcWin", "GetTime", nullptr));
        label_4->setText(QApplication::translate("SfcWin", "\346\235\277\350\276\271\345\217\267\347\240\201", nullptr));
        label_6->setText(QApplication::translate("SfcWin", "\347\273\221\345\256\232\350\265\204\346\226\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SfcWin: public Ui_SfcWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SFCWIN_H
