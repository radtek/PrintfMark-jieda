/********************************************************************************
** Form generated from reading UI file 'offsetsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OFFSETSETUP_H
#define UI_OFFSETSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OffsetSetup
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QLabel *label_Y_2;
    QLabel *label_X_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_4;
    QLabel *label_2;
    QLabel *label_X_3;
    QLabel *label_Y_3;
    QLabel *label_Y_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_7;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_6;
    QPushButton *pushButton_6;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *OffsetSetup)
    {
        if (OffsetSetup->objectName().isEmpty())
            OffsetSetup->setObjectName(QStringLiteral("OffsetSetup"));
        OffsetSetup->resize(379, 420);
        verticalLayout = new QVBoxLayout(OffsetSetup);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(OffsetSetup);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_3, 4, 2, 1, 1, Qt::AlignRight);

        label_Y_2 = new QLabel(groupBox);
        label_Y_2->setObjectName(QStringLiteral("label_Y_2"));
        label_Y_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_Y_2, 0, 2, 1, 1);

        label_X_2 = new QLabel(groupBox);
        label_X_2->setObjectName(QStringLiteral("label_X_2"));
        label_X_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_X_2, 0, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_2, 1, 2, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_4, 2, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(0, 23));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setFrameShadow(QFrame::Sunken);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 3, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(0, 23));
        label_4->setFrameShape(QFrame::Panel);
        label_4->setFrameShadow(QFrame::Sunken);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(OffsetSetup);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label_X_3 = new QLabel(groupBox_2);
        label_X_3->setObjectName(QStringLiteral("label_X_3"));
        label_X_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_X_3, 0, 1, 1, 1);

        label_Y_3 = new QLabel(groupBox_2);
        label_Y_3->setObjectName(QStringLiteral("label_Y_3"));
        label_Y_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_Y_3, 0, 2, 1, 1);

        label_Y_4 = new QLabel(groupBox_2);
        label_Y_4->setObjectName(QStringLiteral("label_Y_4"));
        label_Y_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_Y_4, 0, 3, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        sizePolicy1.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy1);
        lineEdit_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_5, 1, 1, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy1);
        lineEdit_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_6, 1, 2, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 2, 0, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        sizePolicy1.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy1);
        lineEdit_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_9, 2, 2, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        sizePolicy1.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy1);
        lineEdit_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_8, 2, 1, 1, 1);

        lineEdit_10 = new QLineEdit(groupBox_2);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        sizePolicy1.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy1);
        lineEdit_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_10, 2, 3, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        sizePolicy1.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy1);
        lineEdit_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_7, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(0, 23));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setFrameShadow(QFrame::Sunken);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 3, 2, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(0, 23));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setFrameShadow(QFrame::Sunken);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 3, 3, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(0, 23));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 3, 1, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_6, 4, 3, 1, 1, Qt::AlignRight);


        verticalLayout->addWidget(groupBox_2);

        label = new QLabel(OffsetSetup);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        buttonBox = new QDialogButtonBox(OffsetSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(OffsetSetup);

        QMetaObject::connectSlotsByName(OffsetSetup);
    } // setupUi

    void retranslateUi(QWidget *OffsetSetup)
    {
        OffsetSetup->setWindowTitle(QApplication::translate("OffsetSetup", "\345\201\217\347\247\273\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QApplication::translate("OffsetSetup", "\346\227\213\350\275\254", nullptr));
        pushButton_3->setText(QApplication::translate("OffsetSetup", "\350\256\241\347\256\227", nullptr));
        label_Y_2->setText(QApplication::translate("OffsetSetup", "Y", nullptr));
        label_X_2->setText(QApplication::translate("OffsetSetup", "X", nullptr));
        pushButton->setText(QApplication::translate("OffsetSetup", "\345\226\267\347\240\201\344\275\215\347\275\256", nullptr));
        pushButton_2->setText(QApplication::translate("OffsetSetup", "\346\227\213\350\275\254\344\270\255\345\277\203", nullptr));
        label_3->setText(QApplication::translate("OffsetSetup", "\344\270\255\345\277\203\345\201\217\347\247\273", nullptr));
        groupBox_2->setTitle(QApplication::translate("OffsetSetup", "\345\226\267\347\240\201", nullptr));
        pushButton_4->setText(QApplication::translate("OffsetSetup", "\345\226\267\347\240\201\344\275\215\347\275\256", nullptr));
        label_2->setText(QApplication::translate("OffsetSetup", "\345\201\217\347\247\273", nullptr));
        label_X_3->setText(QApplication::translate("OffsetSetup", "X", nullptr));
        label_Y_3->setText(QApplication::translate("OffsetSetup", "Y", nullptr));
        label_Y_4->setText(QApplication::translate("OffsetSetup", "U", nullptr));
        pushButton_5->setText(QApplication::translate("OffsetSetup", "\347\233\270\346\234\272\344\275\215\347\275\256", nullptr));
        pushButton_6->setText(QApplication::translate("OffsetSetup", "\350\256\241\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OffsetSetup: public Ui_OffsetSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OFFSETSETUP_H
