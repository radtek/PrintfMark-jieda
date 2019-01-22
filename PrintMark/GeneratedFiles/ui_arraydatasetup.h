/********************************************************************************
** Form generated from reading UI file 'arraydatasetup.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRAYDATASETUP_H
#define UI_ARRAYDATASETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArrayDataSetup
{
public:
    QAction *actionGet;
    QAction *actionGet_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QLabel *label_7;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QWidget *ArrayDataSetup)
    {
        if (ArrayDataSetup->objectName().isEmpty())
            ArrayDataSetup->setObjectName(QStringLiteral("ArrayDataSetup"));
        ArrayDataSetup->resize(544, 520);
        actionGet = new QAction(ArrayDataSetup);
        actionGet->setObjectName(QStringLiteral("actionGet"));
        actionGet_2 = new QAction(ArrayDataSetup);
        actionGet_2->setObjectName(QStringLiteral("actionGet_2"));
        gridLayout_2 = new QGridLayout(ArrayDataSetup);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButton = new QPushButton(ArrayDataSetup);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_3 = new QPushButton(ArrayDataSetup);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        label_7 = new QLabel(ArrayDataSetup);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_2->addWidget(label_7);


        gridLayout_2->addLayout(verticalLayout_2, 2, 2, 2, 1);

        tableWidget = new QTableWidget(ArrayDataSetup);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable);
        tableWidget->setItem(0, 2, __qtablewidgetitem5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setAlternatingRowColors(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(80);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setDefaultSectionSize(23);

        gridLayout_2->addWidget(tableWidget, 3, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(ArrayDataSetup);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(ArrayDataSetup);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(ArrayDataSetup);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMinimum(-1000);
        doubleSpinBox->setMaximum(1000);

        gridLayout->addWidget(doubleSpinBox, 1, 1, 1, 1);

        label = new QLabel(ArrayDataSetup);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(ArrayDataSetup);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(ArrayDataSetup);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(1);

        gridLayout->addWidget(spinBox_2, 0, 3, 1, 1);

        label_2 = new QLabel(ArrayDataSetup);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(ArrayDataSetup);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        lineEdit = new QLineEdit(ArrayDataSetup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setContextMenuPolicy(Qt::ActionsContextMenu);

        horizontalLayout->addWidget(lineEdit);

        label_6 = new QLabel(ArrayDataSetup);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        lineEdit_2 = new QLineEdit(ArrayDataSetup);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setContextMenuPolicy(Qt::ActionsContextMenu);

        horizontalLayout->addWidget(lineEdit_2);

        label_8 = new QLabel(ArrayDataSetup);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout->addWidget(label_8);

        lineEdit_3 = new QLineEdit(ArrayDataSetup);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setContextMenuPolicy(Qt::ActionsContextMenu);

        horizontalLayout->addWidget(lineEdit_3);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 4);

        doubleSpinBox_2 = new QDoubleSpinBox(ArrayDataSetup);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMinimum(-1000);
        doubleSpinBox_2->setMaximum(1000);

        gridLayout->addWidget(doubleSpinBox_2, 1, 3, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(3, 1);

        gridLayout_2->addLayout(gridLayout, 2, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

        gridLayout_2->addLayout(verticalLayout_3, 1, 0, 1, 1);


        retranslateUi(ArrayDataSetup);

        QMetaObject::connectSlotsByName(ArrayDataSetup);
    } // setupUi

    void retranslateUi(QWidget *ArrayDataSetup)
    {
        ArrayDataSetup->setWindowTitle(QApplication::translate("ArrayDataSetup", "arraydatasetup", nullptr));
        actionGet->setText(QApplication::translate("ArrayDataSetup", "\350\216\267\345\217\226", nullptr));
        actionGet_2->setText(QApplication::translate("ArrayDataSetup", "\350\216\267\345\217\226", nullptr));
        pushButton->setText(QApplication::translate("ArrayDataSetup", "\347\224\237\346\210\220\346\225\260\346\215\256", nullptr));
        pushButton_3->setText(QApplication::translate("ArrayDataSetup", "\345\205\263\351\227\255", nullptr));
        label_7->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ArrayDataSetup", "X\345\201\217\347\247\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ArrayDataSetup", "Y\345\201\217\347\247\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ArrayDataSetup", "\346\227\213\350\275\254", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("ArrayDataSetup", "0.000", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("ArrayDataSetup", "0.000", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 2);
        ___qtablewidgetitem5->setText(QApplication::translate("ArrayDataSetup", "0", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("ArrayDataSetup", "X\350\267\235\347\246\273", nullptr));
        label_4->setText(QApplication::translate("ArrayDataSetup", "Y\350\267\235\347\246\273", nullptr));
        label->setText(QApplication::translate("ArrayDataSetup", "\345\210\227(X)\344\270\252\346\225\260", nullptr));
        label_2->setText(QApplication::translate("ArrayDataSetup", "\350\241\214(Y)\344\270\252\346\225\260", nullptr));
        label_5->setText(QApplication::translate("ArrayDataSetup", "\345\216\237\347\202\271X", nullptr));
        label_6->setText(QApplication::translate("ArrayDataSetup", "\345\216\237\347\202\271Y", nullptr));
        label_8->setText(QApplication::translate("ArrayDataSetup", "\346\226\271\345\220\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArrayDataSetup: public Ui_ArrayDataSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARRAYDATASETUP_H
