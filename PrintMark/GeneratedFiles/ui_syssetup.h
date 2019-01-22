/********************************************************************************
** Form generated from reading UI file 'syssetup.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSSETUP_H
#define UI_SYSSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SysSetup
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QLineEdit *pulseValueZ;
    QLineEdit *pulseValueY;
    QLineEdit *pulseValueX;
    QLabel *label_9;
    QLabel *label_15;
    QLabel *label_19;
    QLabel *label_14;
    QLineEdit *pulseValueU;
    QLabel *label_18;
    QLabel *label_17;
    QLabel *label_16;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_49;
    QLabel *label_6;
    QLabel *label_5;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_11;
    QLabel *label_50;
    QLabel *label_12;
    QSpinBox *spinBox_3;
    QLabel *label_3;
    QCheckBox *checkBox;
    QLabel *label_4;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QLabel *label_7;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *comboBox_3;
    QLabel *label_10;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox_2;
    QLabel *label_2;

    void setupUi(QDialog *SysSetup)
    {
        if (SysSetup->objectName().isEmpty())
            SysSetup->setObjectName(QStringLiteral("SysSetup"));
        SysSetup->resize(405, 382);
        gridLayout_2 = new QGridLayout(SysSetup);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(SysSetup);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 1, 2, 1, 1);

        pulseValueZ = new QLineEdit(groupBox_2);
        pulseValueZ->setObjectName(QStringLiteral("pulseValueZ"));
        pulseValueZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(pulseValueZ, 2, 1, 1, 1);

        pulseValueY = new QLineEdit(groupBox_2);
        pulseValueY->setObjectName(QStringLiteral("pulseValueY"));
        pulseValueY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(pulseValueY, 1, 1, 1, 1);

        pulseValueX = new QLineEdit(groupBox_2);
        pulseValueX->setObjectName(QStringLiteral("pulseValueX"));
        pulseValueX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(pulseValueX, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 0, 2, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setText(QStringLiteral("X"));

        gridLayout->addWidget(label_15, 0, 0, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 3, 2, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 2, 2, 1, 1);

        pulseValueU = new QLineEdit(groupBox_2);
        pulseValueU->setObjectName(QStringLiteral("pulseValueU"));
        pulseValueU->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(pulseValueU, 3, 1, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setText(QStringLiteral("U"));

        gridLayout->addWidget(label_18, 3, 0, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setText(QStringLiteral("Z"));

        gridLayout->addWidget(label_17, 2, 0, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setText(QStringLiteral("Y"));

        gridLayout->addWidget(label_16, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        doubleSpinBox = new QDoubleSpinBox(SysSetup);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setMinimum(-200);
        doubleSpinBox->setMaximum(200);

        gridLayout_5->addWidget(doubleSpinBox, 0, 1, 1, 1);

        label_49 = new QLabel(SysSetup);
        label_49->setObjectName(QStringLiteral("label_49"));

        gridLayout_5->addWidget(label_49, 0, 0, 1, 1);

        label_6 = new QLabel(SysSetup);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 1, 2, 1, 1);

        label_5 = new QLabel(SysSetup);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);

        spinBox = new QSpinBox(SysSetup);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(10);
        spinBox->setMaximum(100);
        spinBox->setSingleStep(5);
        spinBox->setValue(30);

        gridLayout_5->addWidget(spinBox, 1, 1, 1, 1);

        spinBox_2 = new QSpinBox(SysSetup);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(100);
        spinBox_2->setSingleStep(10);
        spinBox_2->setValue(50);

        gridLayout_5->addWidget(spinBox_2, 2, 1, 1, 1);

        label_11 = new QLabel(SysSetup);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_5->addWidget(label_11, 2, 0, 1, 1);

        label_50 = new QLabel(SysSetup);
        label_50->setObjectName(QStringLiteral("label_50"));

        gridLayout_5->addWidget(label_50, 0, 2, 1, 1);

        label_12 = new QLabel(SysSetup);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_5->addWidget(label_12, 3, 0, 1, 1);

        spinBox_3 = new QSpinBox(SysSetup);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(9999);

        gridLayout_5->addWidget(spinBox_3, 3, 1, 1, 1);

        label_3 = new QLabel(SysSetup);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 3, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        checkBox = new QCheckBox(SysSetup);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);


        gridLayout_2->addLayout(verticalLayout, 1, 1, 1, 1);

        label_4 = new QLabel(SysSetup);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(SysSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 3, 1, 1, 1);

        groupBox = new QGroupBox(SysSetup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 48, 36, 16));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 22, 18, 16));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 20, 111, 20));
        comboBox->setEditable(true);
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 40, 261, 51));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        comboBox_3 = new QComboBox(widget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        horizontalLayout_4->addWidget(comboBox_3);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_4->addWidget(label_10);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(true);

        gridLayout_4->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout_4->addWidget(radioButton_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEdit);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_8);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setMaximumSize(QSize(41, 20));

        horizontalLayout->addWidget(lineEdit_2);


        gridLayout_4->addLayout(horizontalLayout, 1, 1, 1, 1);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(234, 22, 121, 20));
        comboBox_2->setEditable(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 20, 18, 16));

        gridLayout_2->addWidget(groupBox, 0, 0, 1, 2);


        retranslateUi(SysSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), SysSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SysSetup, SLOT(reject()));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), comboBox_3, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), lineEdit, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), lineEdit_2, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(SysSetup);
    } // setupUi

    void retranslateUi(QDialog *SysSetup)
    {
        SysSetup->setWindowTitle(QApplication::translate("SysSetup", "\347\263\273\347\273\237\345\217\202\346\225\260", nullptr));
        groupBox_2->setTitle(QApplication::translate("SysSetup", "\350\204\211\345\206\262\345\275\223\351\207\217", nullptr));
        label_13->setText(QApplication::translate("SysSetup", "\346\257\253\347\261\263/\350\204\211\345\206\262", nullptr));
        label_9->setText(QApplication::translate("SysSetup", "\346\257\253\347\261\263/\350\204\211\345\206\262", nullptr));
        label_19->setText(QApplication::translate("SysSetup", "\350\247\222\345\272\246/\350\204\211\345\206\262", nullptr));
        label_14->setText(QApplication::translate("SysSetup", "\346\257\253\347\261\263/\350\204\211\345\206\262", nullptr));
        label_49->setText(QApplication::translate("SysSetup", "Z\350\275\264\345\256\211\345\205\250\351\253\230\345\272\246", nullptr));
        label_6->setText(QApplication::translate("SysSetup", "\346\257\253\347\247\222", nullptr));
        label_5->setText(QApplication::translate("SysSetup", "\345\256\232\346\227\266\345\231\250\347\262\276\345\272\246", nullptr));
        spinBox_2->setSuffix(QApplication::translate("SysSetup", "%", nullptr));
        label_11->setText(QApplication::translate("SysSetup", "\346\211\213\345\212\250\351\200\237\347\216\207", nullptr));
        label_50->setText(QApplication::translate("SysSetup", "\346\257\253\347\261\263", nullptr));
        label_12->setText(QApplication::translate("SysSetup", "\344\277\235\345\205\273\351\227\264\351\232\224\346\227\266\351\227\264", nullptr));
        label_3->setText(QApplication::translate("SysSetup", "\345\260\217\346\227\266", nullptr));
        checkBox->setText(QApplication::translate("SysSetup", "\350\277\220\350\241\214\344\270\255\346\211\223\345\274\200\345\211\215\345\220\216\351\227\250\345\201\234\346\255\242", nullptr));
        groupBox->setTitle(QApplication::translate("SysSetup", "\351\200\232\350\256\257\347\253\257\345\217\243", nullptr));
        label_7->setText(QApplication::translate("SysSetup", "\345\226\267\347\240\201\346\234\272", nullptr));
        label->setText(QApplication::translate("SysSetup", "A\346\235\277", nullptr));
        radioButton->setText(QApplication::translate("SysSetup", "\344\270\262\345\217\243", nullptr));
        radioButton_2->setText(QApplication::translate("SysSetup", "TCP/IP", nullptr));
        lineEdit->setText(QApplication::translate("SysSetup", "0.0.0.0", nullptr));
        label_8->setText(QApplication::translate("SysSetup", ":", nullptr));
        lineEdit_2->setText(QApplication::translate("SysSetup", "2800", nullptr));
        label_2->setText(QApplication::translate("SysSetup", "B\346\235\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SysSetup: public Ui_SysSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSSETUP_H
