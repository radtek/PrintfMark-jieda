/********************************************************************************
** Form generated from reading UI file 'ink.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INK_H
#define UI_INK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ink
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QWidget *tab_4;
    QLabel *label;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QSpinBox *spinBox;
    QLabel *label_11;
    QPushButton *pushButton_7;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_18;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_17;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_26;
    QCheckBox *checkBox_23;
    QCheckBox *checkBox_29;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_19;
    QCheckBox *checkBox_24;
    QCheckBox *checkBox_21;
    QCheckBox *checkBox_20;
    QCheckBox *checkBox_27;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox;
    QCheckBox *checkBox_30;
    QCheckBox *checkBox_25;
    QCheckBox *checkBox_28;
    QCheckBox *checkBox_22;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_31;
    QCheckBox *checkBox_32;
    QCheckBox *checkBox_33;
    QCheckBox *checkBox_34;
    QCheckBox *checkBox_35;
    QCheckBox *checkBox_36;
    QPushButton *pushButton_6;
    QSpinBox *spinBox_2;
    QWidget *tab_5;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget_4;
    QWidget *tab_7;
    QListWidget *listWidget;
    QWidget *tab_2;
    QListWidget *listWidget_2;
    QWidget *tab_6;
    QListWidget *listWidget_3;
    QWidget *tab_8;
    QListWidget *listWidget_4;
    QWidget *tab_9;
    QListWidget *listWidget_5;

    void setupUi(QDialog *ink)
    {
        if (ink->objectName().isEmpty())
            ink->setObjectName(QStringLiteral("ink"));
        ink->resize(808, 720);
        verticalLayout = new QVBoxLayout(ink);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(ink);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(270, 10, 501, 401));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        lineEdit = new QLineEdit(tab_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 30, 301, 31));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 30, 91, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        pushButton->setFont(font);
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label = new QLabel(tab_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 10, 72, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(18);
        label->setFont(font1);
        pushButton_2 = new QPushButton(tab_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 210, 91, 41));
        pushButton_2->setFont(font);
        lineEdit_5 = new QLineEdit(tab_4);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(10, 10, 321, 41));
        lineEdit_6 = new QLineEdit(tab_4);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(10, 60, 331, 41));
        spinBox = new QSpinBox(tab_4);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(350, 150, 51, 31));
        spinBox->setSingleStep(1);
        spinBox->setValue(4);
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(420, 150, 71, 31));
        label_11->setFont(font1);
        pushButton_7 = new QPushButton(tab_4);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(350, 60, 93, 31));
        gridLayoutWidget = new QWidget(tab_4);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 110, 331, 241));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_7 = new QCheckBox(gridLayoutWidget);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));

        gridLayout->addWidget(checkBox_7, 1, 0, 1, 1);

        checkBox_18 = new QCheckBox(gridLayoutWidget);
        checkBox_18->setObjectName(QStringLiteral("checkBox_18"));

        gridLayout->addWidget(checkBox_18, 2, 5, 1, 1);

        checkBox_5 = new QCheckBox(gridLayoutWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 0, 4, 1, 1);

        checkBox_9 = new QCheckBox(gridLayoutWidget);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));

        gridLayout->addWidget(checkBox_9, 1, 2, 1, 1);

        checkBox_6 = new QCheckBox(gridLayoutWidget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        gridLayout->addWidget(checkBox_6, 0, 5, 1, 1);

        checkBox_4 = new QCheckBox(gridLayoutWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 0, 3, 1, 1);

        checkBox_8 = new QCheckBox(gridLayoutWidget);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));

        gridLayout->addWidget(checkBox_8, 1, 1, 1, 1);

        checkBox_16 = new QCheckBox(gridLayoutWidget);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));

        gridLayout->addWidget(checkBox_16, 2, 3, 1, 1);

        checkBox_17 = new QCheckBox(gridLayoutWidget);
        checkBox_17->setObjectName(QStringLiteral("checkBox_17"));

        gridLayout->addWidget(checkBox_17, 2, 4, 1, 1);

        checkBox_14 = new QCheckBox(gridLayoutWidget);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));

        gridLayout->addWidget(checkBox_14, 2, 1, 1, 1);

        checkBox_26 = new QCheckBox(gridLayoutWidget);
        checkBox_26->setObjectName(QStringLiteral("checkBox_26"));

        gridLayout->addWidget(checkBox_26, 4, 1, 1, 1);

        checkBox_23 = new QCheckBox(gridLayoutWidget);
        checkBox_23->setObjectName(QStringLiteral("checkBox_23"));

        gridLayout->addWidget(checkBox_23, 3, 4, 1, 1);

        checkBox_29 = new QCheckBox(gridLayoutWidget);
        checkBox_29->setObjectName(QStringLiteral("checkBox_29"));

        gridLayout->addWidget(checkBox_29, 4, 4, 1, 1);

        checkBox_10 = new QCheckBox(gridLayoutWidget);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));

        gridLayout->addWidget(checkBox_10, 1, 3, 1, 1);

        checkBox_19 = new QCheckBox(gridLayoutWidget);
        checkBox_19->setObjectName(QStringLiteral("checkBox_19"));

        gridLayout->addWidget(checkBox_19, 3, 0, 1, 1);

        checkBox_24 = new QCheckBox(gridLayoutWidget);
        checkBox_24->setObjectName(QStringLiteral("checkBox_24"));

        gridLayout->addWidget(checkBox_24, 3, 5, 1, 1);

        checkBox_21 = new QCheckBox(gridLayoutWidget);
        checkBox_21->setObjectName(QStringLiteral("checkBox_21"));

        gridLayout->addWidget(checkBox_21, 3, 2, 1, 1);

        checkBox_20 = new QCheckBox(gridLayoutWidget);
        checkBox_20->setObjectName(QStringLiteral("checkBox_20"));

        gridLayout->addWidget(checkBox_20, 3, 1, 1, 1);

        checkBox_27 = new QCheckBox(gridLayoutWidget);
        checkBox_27->setObjectName(QStringLiteral("checkBox_27"));

        gridLayout->addWidget(checkBox_27, 4, 2, 1, 1);

        checkBox_15 = new QCheckBox(gridLayoutWidget);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));

        gridLayout->addWidget(checkBox_15, 2, 2, 1, 1);

        checkBox = new QCheckBox(gridLayoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_30 = new QCheckBox(gridLayoutWidget);
        checkBox_30->setObjectName(QStringLiteral("checkBox_30"));

        gridLayout->addWidget(checkBox_30, 4, 5, 1, 1);

        checkBox_25 = new QCheckBox(gridLayoutWidget);
        checkBox_25->setObjectName(QStringLiteral("checkBox_25"));

        gridLayout->addWidget(checkBox_25, 4, 0, 1, 1);

        checkBox_28 = new QCheckBox(gridLayoutWidget);
        checkBox_28->setObjectName(QStringLiteral("checkBox_28"));

        gridLayout->addWidget(checkBox_28, 4, 3, 1, 1);

        checkBox_22 = new QCheckBox(gridLayoutWidget);
        checkBox_22->setObjectName(QStringLiteral("checkBox_22"));

        gridLayout->addWidget(checkBox_22, 3, 3, 1, 1);

        checkBox_11 = new QCheckBox(gridLayoutWidget);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));

        gridLayout->addWidget(checkBox_11, 1, 4, 1, 1);

        checkBox_13 = new QCheckBox(gridLayoutWidget);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));

        gridLayout->addWidget(checkBox_13, 2, 0, 1, 1);

        checkBox_12 = new QCheckBox(gridLayoutWidget);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));

        gridLayout->addWidget(checkBox_12, 1, 5, 1, 1);

        checkBox_2 = new QCheckBox(gridLayoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 0, 1, 1, 1);

        checkBox_3 = new QCheckBox(gridLayoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 0, 2, 1, 1);

        checkBox_31 = new QCheckBox(gridLayoutWidget);
        checkBox_31->setObjectName(QStringLiteral("checkBox_31"));

        gridLayout->addWidget(checkBox_31, 5, 0, 1, 1);

        checkBox_32 = new QCheckBox(gridLayoutWidget);
        checkBox_32->setObjectName(QStringLiteral("checkBox_32"));

        gridLayout->addWidget(checkBox_32, 5, 1, 1, 1);

        checkBox_33 = new QCheckBox(gridLayoutWidget);
        checkBox_33->setObjectName(QStringLiteral("checkBox_33"));

        gridLayout->addWidget(checkBox_33, 5, 2, 1, 1);

        checkBox_34 = new QCheckBox(gridLayoutWidget);
        checkBox_34->setObjectName(QStringLiteral("checkBox_34"));

        gridLayout->addWidget(checkBox_34, 5, 3, 1, 1);

        checkBox_35 = new QCheckBox(gridLayoutWidget);
        checkBox_35->setObjectName(QStringLiteral("checkBox_35"));

        gridLayout->addWidget(checkBox_35, 5, 4, 1, 1);

        checkBox_36 = new QCheckBox(gridLayoutWidget);
        checkBox_36->setObjectName(QStringLiteral("checkBox_36"));
        checkBox_36->setChecked(false);

        gridLayout->addWidget(checkBox_36, 5, 5, 1, 1);

        pushButton_6 = new QPushButton(tab_4);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(430, 320, 51, 41));
        spinBox_2 = new QSpinBox(tab_4);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(350, 320, 51, 31));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(999);
        spinBox_2->setValue(1);
        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        radioButton = new QRadioButton(tab_5);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(30, 150, 91, 16));
        radioButton_2 = new QRadioButton(tab_5);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(30, 110, 131, 16));
        radioButton_3 = new QRadioButton(tab_5);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(30, 64, 91, 16));
        dateTimeEdit = new QDateTimeEdit(tab_5);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setEnabled(false);
        dateTimeEdit->setGeometry(QRect(30, 20, 131, 22));
        label_3 = new QLabel(tab_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(180, 10, 121, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(16);
        label_3->setFont(font2);
        lineEdit_2 = new QLineEdit(tab_5);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setEnabled(true);
        lineEdit_2->setGeometry(QRect(160, 110, 181, 31));
        lineEdit_2->setCursorPosition(0);
        lineEdit_2->setReadOnly(true);
        label_4 = new QLabel(tab_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 70, 141, 31));
        label_4->setFont(font2);
        pushButton_3 = new QPushButton(tab_5);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(380, 150, 91, 41));
        pushButton_3->setFont(font);
        tabWidget_2->addTab(tab_5, QString());
        pushButton_4 = new QPushButton(tab);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(160, 430, 91, 51));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 490, 171, 31));
        label_5->setFont(font2);
        lineEdit_3 = new QLineEdit(tab);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 540, 641, 51));
        lineEdit_3->setReadOnly(true);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(660, 550, 91, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(14);
        pushButton_5->setFont(font3);
        buttonBox = new QDialogButtonBox(tab);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(530, 610, 221, 41));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(14);
        buttonBox->setFont(font4);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget_4 = new QTabWidget(tab);
        tabWidget_4->setObjectName(QStringLiteral("tabWidget_4"));
        tabWidget_4->setGeometry(QRect(0, 0, 261, 431));
        tabWidget_4->setIconSize(QSize(20, 20));
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        listWidget = new QListWidget(tab_7);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 251, 401));
        tabWidget_4->addTab(tab_7, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listWidget_2 = new QListWidget(tab_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(0, 0, 251, 401));
        tabWidget_4->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        listWidget_3 = new QListWidget(tab_6);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));
        listWidget_3->setGeometry(QRect(0, 0, 251, 401));
        tabWidget_4->addTab(tab_6, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        listWidget_4 = new QListWidget(tab_8);
        listWidget_4->setObjectName(QStringLiteral("listWidget_4"));
        listWidget_4->setGeometry(QRect(0, 0, 251, 401));
        tabWidget_4->addTab(tab_8, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        listWidget_5 = new QListWidget(tab_9);
        listWidget_5->setObjectName(QStringLiteral("listWidget_5"));
        listWidget_5->setGeometry(QRect(0, 0, 251, 401));
        tabWidget_4->addTab(tab_9, QString());
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ink);
        QObject::connect(buttonBox, SIGNAL(accepted()), ink, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ink, SLOT(reject()));

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);
        tabWidget_4->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ink);
    } // setupUi

    void retranslateUi(QDialog *ink)
    {
        ink->setWindowTitle(QApplication::translate("ink", "ink", nullptr));
        pushButton->setText(QApplication::translate("ink", "\346\267\273\345\212\240\346\226\207\346\234\254", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("ink", "\350\257\255\350\250\200\346\226\207\346\234\254", nullptr));
        label->setText(QApplication::translate("ink", "\346\225\260\351\207\217", nullptr));
        pushButton_2->setText(QApplication::translate("ink", "\346\267\273\345\212\240\346\226\207\346\234\254", nullptr));
        label_11->setText(QApplication::translate("ink", "\344\275\215\346\225\260", nullptr));
        pushButton_7->setText(QApplication::translate("ink", "\344\270\212\345\215\207\345\272\217\345\210\227", nullptr));
        checkBox_7->setText(QApplication::translate("ink", "6", nullptr));
        checkBox_18->setText(QApplication::translate("ink", "H", nullptr));
        checkBox_5->setText(QApplication::translate("ink", "4", nullptr));
        checkBox_9->setText(QApplication::translate("ink", "8", nullptr));
        checkBox_6->setText(QApplication::translate("ink", "5", nullptr));
        checkBox_4->setText(QApplication::translate("ink", "3", nullptr));
        checkBox_8->setText(QApplication::translate("ink", "7", nullptr));
        checkBox_16->setText(QApplication::translate("ink", "F", nullptr));
        checkBox_17->setText(QApplication::translate("ink", "G", nullptr));
        checkBox_14->setText(QApplication::translate("ink", "D", nullptr));
        checkBox_26->setText(QApplication::translate("ink", "P", nullptr));
        checkBox_23->setText(QApplication::translate("ink", "M", nullptr));
        checkBox_29->setText(QApplication::translate("ink", "S", nullptr));
        checkBox_10->setText(QApplication::translate("ink", "9", nullptr));
        checkBox_19->setText(QApplication::translate("ink", "I", nullptr));
        checkBox_24->setText(QApplication::translate("ink", "N", nullptr));
        checkBox_21->setText(QApplication::translate("ink", "K", nullptr));
        checkBox_20->setText(QApplication::translate("ink", "J", nullptr));
        checkBox_27->setText(QApplication::translate("ink", "Q", nullptr));
        checkBox_15->setText(QApplication::translate("ink", "E", nullptr));
        checkBox->setText(QApplication::translate("ink", "0", nullptr));
        checkBox_30->setText(QApplication::translate("ink", "T", nullptr));
        checkBox_25->setText(QApplication::translate("ink", "O", nullptr));
        checkBox_28->setText(QApplication::translate("ink", "R", nullptr));
        checkBox_22->setText(QApplication::translate("ink", "L", nullptr));
        checkBox_11->setText(QApplication::translate("ink", "A", nullptr));
        checkBox_13->setText(QApplication::translate("ink", "C", nullptr));
        checkBox_12->setText(QApplication::translate("ink", "B", nullptr));
        checkBox_2->setText(QApplication::translate("ink", "1", nullptr));
        checkBox_3->setText(QApplication::translate("ink", "2", nullptr));
        checkBox_31->setText(QApplication::translate("ink", "U", nullptr));
        checkBox_32->setText(QApplication::translate("ink", "V", nullptr));
        checkBox_33->setText(QApplication::translate("ink", "W", nullptr));
        checkBox_34->setText(QApplication::translate("ink", "X", nullptr));
        checkBox_35->setText(QApplication::translate("ink", "Y", nullptr));
        checkBox_36->setText(QApplication::translate("ink", "Z", nullptr));
        pushButton_6->setText(QApplication::translate("ink", "\346\255\245\351\225\277", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("ink", "\350\256\241\346\225\260\346\226\207\346\234\254", nullptr));
        radioButton->setText(QApplication::translate("ink", "MM.dd", nullptr));
        radioButton_2->setText(QApplication::translate("ink", "yyyy.MM.dd", nullptr));
        radioButton_3->setText(QApplication::translate("ink", "yy.MM.dd", nullptr));
        label_3->setText(QApplication::translate("ink", "\346\227\266\351\227\264\346\226\207\346\234\254", nullptr));
        lineEdit_2->setInputMask(QString());
        label_4->setText(QApplication::translate("ink", "\351\242\204\350\247\210\346\225\210\346\236\234", nullptr));
        pushButton_3->setText(QApplication::translate("ink", "\346\267\273\345\212\240\346\226\207\346\234\254", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("ink", "\346\227\266\351\227\264\346\226\207\346\234\254", nullptr));
        pushButton_4->setText(QApplication::translate("ink", "\345\210\240\351\231\244", nullptr));
        label_5->setText(QApplication::translate("ink", "\351\242\204\350\247\210\346\211\223\345\215\260\344\277\241\346\201\257", nullptr));
        pushButton_5->setText(QApplication::translate("ink", "\346\233\264\346\226\260", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_7), QApplication::translate("ink", "\344\277\241\346\201\2571", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_2), QApplication::translate("ink", "\344\277\241\346\201\2572", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_6), QApplication::translate("ink", "\344\277\241\346\201\2573", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_8), QApplication::translate("ink", "\344\277\241\346\201\2574", nullptr));
        tabWidget_4->setTabText(tabWidget_4->indexOf(tab_9), QApplication::translate("ink", "\344\277\241\346\201\2575", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ink", "\345\226\267\345\215\260\345\217\202\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ink: public Ui_ink {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INK_H
