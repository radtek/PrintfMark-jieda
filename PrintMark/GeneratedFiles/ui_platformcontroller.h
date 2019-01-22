/********************************************************************************
** Form generated from reading UI file 'platformcontroller.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLATFORMCONTROLLER_H
#define UI_PLATFORMCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlatformController
{
public:
    QAction *actionHomeX2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QToolButton *buttonUp;
    QToolButton *buttonRight;
    QToolButton *buttonLeft;
    QToolButton *buttonDown;
    QGroupBox *groupBoxSpeed;
    QVBoxLayout *verticalLayout_6;
    QSlider *sliderSpeed;
    QGridLayout *gridLayout_2;
    QToolButton *buttonZup;
    QToolButton *buttonUdown;
    QToolButton *buttonZdown;
    QToolButton *buttonUup;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QToolButton *buttonStop;
    QToolButton *buttonHome;
    QLabel *labelStatus;
    QCheckBox *checkBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLabel *labelPosX;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLabel *labelPosY;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_2;
    QLabel *labelPosZ;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_4;
    QLabel *labelPosU;
    QLabel *label_8;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QLabel *label_20;
    QLabel *label_16;
    QLabel *label_22;
    QLabel *label_21;
    QLabel *label_19;
    QToolButton *buttonGotoZ;
    QToolButton *buttonGotoY;
    QLabel *label_18;
    QLabel *label_17;
    QDoubleSpinBox *gotoX;
    QDoubleSpinBox *gotoY;
    QDoubleSpinBox *gotoZ;
    QDoubleSpinBox *gotoU;
    QToolButton *buttonGotoU;
    QLabel *label_23;
    QToolButton *buttonGotoX;

    void setupUi(QWidget *PlatformController)
    {
        if (PlatformController->objectName().isEmpty())
            PlatformController->setObjectName(QStringLiteral("PlatformController"));
        PlatformController->resize(469, 322);
        PlatformController->setFocusPolicy(Qt::ClickFocus);
        actionHomeX2 = new QAction(PlatformController);
        actionHomeX2->setObjectName(QStringLiteral("actionHomeX2"));
        horizontalLayout_3 = new QHBoxLayout(PlatformController);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(PlatformController);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        buttonUp = new QToolButton(groupBox_3);
        buttonUp->setObjectName(QStringLiteral("buttonUp"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/Arrow Up.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonUp->setIcon(icon);
        buttonUp->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(buttonUp, 0, 1, 1, 1);

        buttonRight = new QToolButton(groupBox_3);
        buttonRight->setObjectName(QStringLiteral("buttonRight"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/Arrow Forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonRight->setIcon(icon1);
        buttonRight->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(buttonRight, 1, 3, 1, 1);

        buttonLeft = new QToolButton(groupBox_3);
        buttonLeft->setObjectName(QStringLiteral("buttonLeft"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/Arrow Back.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonLeft->setIcon(icon2);
        buttonLeft->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(buttonLeft, 1, 0, 1, 1);

        buttonDown = new QToolButton(groupBox_3);
        buttonDown->setObjectName(QStringLiteral("buttonDown"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/Arrow Down.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDown->setIcon(icon3);
        buttonDown->setIconSize(QSize(32, 32));

        gridLayout_3->addWidget(buttonDown, 2, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_3);

        groupBoxSpeed = new QGroupBox(PlatformController);
        groupBoxSpeed->setObjectName(QStringLiteral("groupBoxSpeed"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxSpeed->sizePolicy().hasHeightForWidth());
        groupBoxSpeed->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(groupBoxSpeed);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        sliderSpeed = new QSlider(groupBoxSpeed);
        sliderSpeed->setObjectName(QStringLiteral("sliderSpeed"));
        sizePolicy.setHeightForWidth(sliderSpeed->sizePolicy().hasHeightForWidth());
        sliderSpeed->setSizePolicy(sizePolicy);
        sliderSpeed->setMaximum(4);
        sliderSpeed->setPageStep(1);
        sliderSpeed->setOrientation(Qt::Vertical);
        sliderSpeed->setTickPosition(QSlider::TicksBelow);
        sliderSpeed->setTickInterval(1);

        verticalLayout_6->addWidget(sliderSpeed);


        horizontalLayout->addWidget(groupBoxSpeed);


        verticalLayout_3->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        buttonZup = new QToolButton(PlatformController);
        buttonZup->setObjectName(QStringLiteral("buttonZup"));
        buttonZup->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/Raise.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonZup->setIcon(icon4);
        buttonZup->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(buttonZup, 0, 0, 1, 1);

        buttonUdown = new QToolButton(PlatformController);
        buttonUdown->setObjectName(QStringLiteral("buttonUdown"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/cw.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonUdown->setIcon(icon5);
        buttonUdown->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(buttonUdown, 0, 3, 1, 1);

        buttonZdown = new QToolButton(PlatformController);
        buttonZdown->setObjectName(QStringLiteral("buttonZdown"));
        buttonZdown->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Resources/Fall.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonZdown->setIcon(icon6);
        buttonZdown->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(buttonZdown, 0, 1, 1, 1);

        buttonUup = new QToolButton(PlatformController);
        buttonUup->setObjectName(QStringLiteral("buttonUup"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Resources/ccw.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonUup->setIcon(icon7);
        buttonUup->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(buttonUup, 0, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout_3->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonStop = new QToolButton(PlatformController);
        buttonStop->setObjectName(QStringLiteral("buttonStop"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonStop->sizePolicy().hasHeightForWidth());
        buttonStop->setSizePolicy(sizePolicy1);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Resources/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStop->setIcon(icon8);
        buttonStop->setIconSize(QSize(40, 40));
        buttonStop->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(buttonStop, 1, 1, 1, 1);

        buttonHome = new QToolButton(PlatformController);
        buttonHome->setObjectName(QStringLiteral("buttonHome"));
        sizePolicy1.setHeightForWidth(buttonHome->sizePolicy().hasHeightForWidth());
        buttonHome->setSizePolicy(sizePolicy1);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Resources/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonHome->setIcon(icon9);
        buttonHome->setIconSize(QSize(40, 40));
        buttonHome->setPopupMode(QToolButton::MenuButtonPopup);
        buttonHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(buttonHome, 1, 0, 1, 1);

        labelStatus = new QLabel(PlatformController);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setStyleSheet(QLatin1String("font: 10pt \"Webdings\";\n"
"color: gold;"));

        gridLayout->addWidget(labelStatus, 0, 1, 1, 1, Qt::AlignRight|Qt::AlignTop);

        checkBox = new QCheckBox(PlatformController);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);

        verticalLayout_3->addLayout(gridLayout);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(PlatformController);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(1);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(4, -1, 4, 4);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        label->setText(QStringLiteral("X:"));

        horizontalLayout_8->addWidget(label);

        labelPosX = new QLabel(groupBox);
        labelPosX->setObjectName(QStringLiteral("labelPosX"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelPosX->sizePolicy().hasHeightForWidth());
        labelPosX->setSizePolicy(sizePolicy2);
        labelPosX->setMinimumSize(QSize(90, 0));
        labelPosX->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        labelPosX->setText(QStringLiteral("0.000"));
        labelPosX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(labelPosX);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(40, 0));
        label_5->setMaximumSize(QSize(48, 16777215));
        label_5->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));

        horizontalLayout_8->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        label_3->setText(QStringLiteral("Y:"));

        horizontalLayout_10->addWidget(label_3);

        labelPosY = new QLabel(groupBox);
        labelPosY->setObjectName(QStringLiteral("labelPosY"));
        sizePolicy2.setHeightForWidth(labelPosY->sizePolicy().hasHeightForWidth());
        labelPosY->setSizePolicy(sizePolicy2);
        labelPosY->setMinimumSize(QSize(90, 0));
        labelPosY->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        labelPosY->setText(QStringLiteral("0.000"));
        labelPosY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(labelPosY);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(40, 0));
        label_7->setMaximumSize(QSize(48, 16777215));
        label_7->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));

        horizontalLayout_10->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        label_2->setText(QStringLiteral("Z:"));

        horizontalLayout_9->addWidget(label_2);

        labelPosZ = new QLabel(groupBox);
        labelPosZ->setObjectName(QStringLiteral("labelPosZ"));
        sizePolicy2.setHeightForWidth(labelPosZ->sizePolicy().hasHeightForWidth());
        labelPosZ->setSizePolicy(sizePolicy2);
        labelPosZ->setMinimumSize(QSize(90, 0));
        labelPosZ->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        labelPosZ->setText(QStringLiteral("0.000"));
        labelPosZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(labelPosZ);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(40, 0));
        label_6->setMaximumSize(QSize(48, 16777215));
        label_6->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));

        horizontalLayout_9->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        label_4->setText(QStringLiteral("U:"));

        horizontalLayout_11->addWidget(label_4);

        labelPosU = new QLabel(groupBox);
        labelPosU->setObjectName(QStringLiteral("labelPosU"));
        sizePolicy2.setHeightForWidth(labelPosU->sizePolicy().hasHeightForWidth());
        labelPosU->setSizePolicy(sizePolicy2);
        labelPosU->setMinimumSize(QSize(90, 0));
        labelPosU->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));
        labelPosU->setText(QStringLiteral("0.000"));
        labelPosU->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(labelPosU);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(40, 0));
        label_8->setMaximumSize(QSize(48, 16777215));
        label_8->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 0);\n"
"font: 16pt \"Arial\";"));

        horizontalLayout_11->addWidget(label_8, 0, Qt::AlignLeft);


        verticalLayout->addLayout(horizontalLayout_11);


        verticalLayout_2->addWidget(groupBox);

        groupBox_4 = new QGroupBox(PlatformController);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setSpacing(1);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(4, -1, 4, 4);
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_20, 3, 0, 1, 1);

        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_16, 1, 0, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_22, 4, 0, 1, 1);

        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_21, 3, 2, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_19, 2, 2, 1, 1);

        buttonGotoZ = new QToolButton(groupBox_4);
        buttonGotoZ->setObjectName(QStringLiteral("buttonGotoZ"));
        buttonGotoZ->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(buttonGotoZ->sizePolicy().hasHeightForWidth());
        buttonGotoZ->setSizePolicy(sizePolicy3);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Resources/Goto.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonGotoZ->setIcon(icon10);
        buttonGotoZ->setIconSize(QSize(32, 32));
        buttonGotoZ->setToolButtonStyle(Qt::ToolButtonIconOnly);

        gridLayout_7->addWidget(buttonGotoZ, 3, 3, 1, 1);

        buttonGotoY = new QToolButton(groupBox_4);
        buttonGotoY->setObjectName(QStringLiteral("buttonGotoY"));
        sizePolicy3.setHeightForWidth(buttonGotoY->sizePolicy().hasHeightForWidth());
        buttonGotoY->setSizePolicy(sizePolicy3);
        buttonGotoY->setIcon(icon10);
        buttonGotoY->setIconSize(QSize(32, 32));
        buttonGotoY->setToolButtonStyle(Qt::ToolButtonIconOnly);

        gridLayout_7->addWidget(buttonGotoY, 2, 3, 1, 1);

        label_18 = new QLabel(groupBox_4);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_18, 2, 0, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_17, 1, 2, 1, 1);

        gotoX = new QDoubleSpinBox(groupBox_4);
        gotoX->setObjectName(QStringLiteral("gotoX"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(gotoX->sizePolicy().hasHeightForWidth());
        gotoX->setSizePolicy(sizePolicy4);
        gotoX->setStyleSheet(QStringLiteral("QDoubleSpinBox{font: 16pt \"Arial\";}"));
        gotoX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gotoX->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        gotoX->setDecimals(3);
        gotoX->setMinimum(-300000);
        gotoX->setMaximum(300000);

        gridLayout_7->addWidget(gotoX, 1, 1, 1, 1);

        gotoY = new QDoubleSpinBox(groupBox_4);
        gotoY->setObjectName(QStringLiteral("gotoY"));
        sizePolicy4.setHeightForWidth(gotoY->sizePolicy().hasHeightForWidth());
        gotoY->setSizePolicy(sizePolicy4);
        gotoY->setStyleSheet(QStringLiteral("QDoubleSpinBox{font: 16pt \"Arial\";}"));
        gotoY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gotoY->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        gotoY->setDecimals(3);
        gotoY->setMinimum(-300000);
        gotoY->setMaximum(300000);

        gridLayout_7->addWidget(gotoY, 2, 1, 1, 1);

        gotoZ = new QDoubleSpinBox(groupBox_4);
        gotoZ->setObjectName(QStringLiteral("gotoZ"));
        gotoZ->setEnabled(false);
        sizePolicy4.setHeightForWidth(gotoZ->sizePolicy().hasHeightForWidth());
        gotoZ->setSizePolicy(sizePolicy4);
        gotoZ->setStyleSheet(QStringLiteral("QDoubleSpinBox{font: 16pt \"Arial\";}"));
        gotoZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gotoZ->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        gotoZ->setDecimals(3);
        gotoZ->setMinimum(-300000);
        gotoZ->setMaximum(300000);

        gridLayout_7->addWidget(gotoZ, 3, 1, 1, 1);

        gotoU = new QDoubleSpinBox(groupBox_4);
        gotoU->setObjectName(QStringLiteral("gotoU"));
        sizePolicy4.setHeightForWidth(gotoU->sizePolicy().hasHeightForWidth());
        gotoU->setSizePolicy(sizePolicy4);
        gotoU->setStyleSheet(QStringLiteral("QDoubleSpinBox{font: 16pt \"Arial\";}"));
        gotoU->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gotoU->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        gotoU->setDecimals(3);
        gotoU->setMinimum(-300000);
        gotoU->setMaximum(300000);

        gridLayout_7->addWidget(gotoU, 4, 1, 1, 1);

        buttonGotoU = new QToolButton(groupBox_4);
        buttonGotoU->setObjectName(QStringLiteral("buttonGotoU"));
        sizePolicy3.setHeightForWidth(buttonGotoU->sizePolicy().hasHeightForWidth());
        buttonGotoU->setSizePolicy(sizePolicy3);
        buttonGotoU->setIcon(icon10);
        buttonGotoU->setIconSize(QSize(32, 32));
        buttonGotoU->setToolButtonStyle(Qt::ToolButtonIconOnly);

        gridLayout_7->addWidget(buttonGotoU, 4, 3, 1, 1);

        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));

        gridLayout_7->addWidget(label_23, 4, 2, 1, 1);

        buttonGotoX = new QToolButton(groupBox_4);
        buttonGotoX->setObjectName(QStringLiteral("buttonGotoX"));
        sizePolicy3.setHeightForWidth(buttonGotoX->sizePolicy().hasHeightForWidth());
        buttonGotoX->setSizePolicy(sizePolicy3);
        buttonGotoX->setIcon(icon10);
        buttonGotoX->setIconSize(QSize(32, 32));
        buttonGotoX->setToolButtonStyle(Qt::ToolButtonIconOnly);

        gridLayout_7->addWidget(buttonGotoX, 1, 3, 1, 1);

        gridLayout_7->setColumnStretch(1, 1);

        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(PlatformController);

        QMetaObject::connectSlotsByName(PlatformController);
    } // setupUi

    void retranslateUi(QWidget *PlatformController)
    {
        PlatformController->setWindowTitle(QApplication::translate("PlatformController", "\345\271\263\345\217\260\346\216\247\345\210\266\345\231\250", nullptr));
        actionHomeX2->setText(QApplication::translate("PlatformController", "X\350\260\203\345\256\275\345\233\236\345\216\237\347\202\271", nullptr));
#ifndef QT_NO_TOOLTIP
        actionHomeX2->setToolTip(QApplication::translate("PlatformController", "X\350\260\203\345\256\275\345\233\236\345\216\237\347\202\271", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_3->setTitle(QApplication::translate("PlatformController", "\345\271\263\345\217\260", nullptr));
        groupBoxSpeed->setTitle(QApplication::translate("PlatformController", "\351\200\237\345\272\246", nullptr));
        buttonStop->setText(QApplication::translate("PlatformController", "\347\253\213\345\215\263\345\201\234\346\255\242", nullptr));
        buttonHome->setText(QApplication::translate("PlatformController", "\345\233\236\345\216\237\347\202\271", nullptr));
        labelStatus->setText(QApplication::translate("PlatformController", "n", nullptr));
        checkBox->setText(QApplication::translate("PlatformController", "\345\242\236\351\207\217\345\256\232\344\275\215", nullptr));
        groupBox->setTitle(QApplication::translate("PlatformController", "\344\275\215\347\275\256", nullptr));
#ifndef QT_NO_STATUSTIP
        labelPosX->setStatusTip(QApplication::translate("PlatformController", "\345\217\214\345\207\273\345\217\263\351\224\256\345\260\206\345\235\220\346\240\207\345\206\231\345\210\260\345\277\253\351\200\237\345\256\232\344\275\215", nullptr));
#endif // QT_NO_STATUSTIP
        label_5->setText(QApplication::translate("PlatformController", "MM", nullptr));
#ifndef QT_NO_STATUSTIP
        labelPosY->setStatusTip(QApplication::translate("PlatformController", "\345\217\214\345\207\273\345\217\263\351\224\256\345\260\206\345\235\220\346\240\207\345\206\231\345\210\260\345\277\253\351\200\237\345\256\232\344\275\215", nullptr));
#endif // QT_NO_STATUSTIP
        label_7->setText(QApplication::translate("PlatformController", "MM", nullptr));
#ifndef QT_NO_STATUSTIP
        labelPosZ->setStatusTip(QApplication::translate("PlatformController", "\345\217\214\345\207\273\345\217\263\351\224\256\345\260\206\345\235\220\346\240\207\345\206\231\345\210\260\345\277\253\351\200\237\345\256\232\344\275\215", nullptr));
#endif // QT_NO_STATUSTIP
        label_6->setText(QApplication::translate("PlatformController", "MM", nullptr));
#ifndef QT_NO_STATUSTIP
        labelPosU->setStatusTip(QApplication::translate("PlatformController", "\345\217\214\345\207\273\345\217\263\351\224\256\345\260\206\345\235\220\346\240\207\345\206\231\345\210\260\345\277\253\351\200\237\345\256\232\344\275\215", nullptr));
#endif // QT_NO_STATUSTIP
        label_8->setText(QApplication::translate("PlatformController", "\302\260", nullptr));
        groupBox_4->setTitle(QApplication::translate("PlatformController", "\345\277\253\351\200\237\345\256\232\344\275\215", nullptr));
        label_20->setText(QApplication::translate("PlatformController", "Z:", nullptr));
        label_16->setText(QApplication::translate("PlatformController", "X:", nullptr));
        label_22->setText(QApplication::translate("PlatformController", "U:", nullptr));
        label_21->setText(QApplication::translate("PlatformController", " MM", nullptr));
        label_19->setText(QApplication::translate("PlatformController", " MM", nullptr));
        buttonGotoZ->setText(QString());
        buttonGotoY->setText(QString());
        label_18->setText(QApplication::translate("PlatformController", "Y:", nullptr));
        label_17->setText(QApplication::translate("PlatformController", " MM", nullptr));
        buttonGotoU->setText(QString());
        label_23->setText(QApplication::translate("PlatformController", " \302\260", nullptr));
        buttonGotoX->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlatformController: public Ui_PlatformController {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLATFORMCONTROLLER_H
