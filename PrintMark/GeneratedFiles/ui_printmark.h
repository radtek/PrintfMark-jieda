/********************************************************************************
** Form generated from reading UI file 'printmark.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTMARK_H
#define UI_PRINTMARK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrintMarkClass
{
public:
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionIoPane;
    QAction *actionSysSetup;
    QAction *actionRunParams;
    QAction *actionCamCalib;
    QAction *actionOffsetSetup;
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionSetMark1;
    QAction *actionSetMark2;
    QAction *actionClear;
    QAction *actionRunCpk;
    QAction *actionSetup;
    QAction *actionReset;
    QAction *actionTest;
    QAction *actionGetPos;
    QAction *actionGoto;
    QAction *actionTGoto;
    QAction *actionTrans;
    QAction *actionSaveAs;
    QAction *actionReadCode;
    QAction *actionGotoCenter;
    QAction *actionTestBadMark;
    QAction *actionSfcWin;
    QAction *actionSfc;
    QAction *actionMaintain1;
    QAction *actionMaintain2;
    QAction *actionNew;
    QAction *actionink;
    QAction *actionArraySetup;
    QAction *actionMovePosition;
    QAction *actiondpyBattery;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *frame;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton;
    QSlider *horizontalSlider;
    QLabel *label_6;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_12;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_22;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QPushButton *pushButton_14;
    QPushButton *pushButton_17;
    QCheckBox *checkBox_8;
    QPushButton *pushButton_23;
    QComboBox *comboBox_2;
    QPushButton *pushButton_24;
    QCheckBox *checkBox_9;
    QPushButton *pushButton_13;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_18;
    QPushButton *pushButton_15;
    QPushButton *pushButton_25;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QCheckBox *checkBox_4;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButton_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *toolButton_3;
    QLabel *label_5;
    QTableWidget *tableWidget_3;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_16;
    QPushButton *pushButton_11;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_26;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QListWidget *listWidget_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QLCDNumber *lcdNumber_3;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_S;
    QMenu *menu_H;
    QMenu *menu_P;
    QMenu *menu_D;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PrintMarkClass)
    {
        if (PrintMarkClass->objectName().isEmpty())
            PrintMarkClass->setObjectName(QStringLiteral("PrintMarkClass"));
        PrintMarkClass->resize(1131, 852);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/printmark.png"), QSize(), QIcon::Normal, QIcon::Off);
        PrintMarkClass->setWindowIcon(icon);
        actionQuit = new QAction(PrintMarkClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionAbout = new QAction(PrintMarkClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionIoPane = new QAction(PrintMarkClass);
        actionIoPane->setObjectName(QStringLiteral("actionIoPane"));
        actionSysSetup = new QAction(PrintMarkClass);
        actionSysSetup->setObjectName(QStringLiteral("actionSysSetup"));
        actionSysSetup->setEnabled(false);
        actionRunParams = new QAction(PrintMarkClass);
        actionRunParams->setObjectName(QStringLiteral("actionRunParams"));
        actionRunParams->setEnabled(false);
        actionCamCalib = new QAction(PrintMarkClass);
        actionCamCalib->setObjectName(QStringLiteral("actionCamCalib"));
        actionOffsetSetup = new QAction(PrintMarkClass);
        actionOffsetSetup->setObjectName(QStringLiteral("actionOffsetSetup"));
        actionLoad = new QAction(PrintMarkClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/Load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon1);
        actionSave = new QAction(PrintMarkClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/saveimage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSetMark1 = new QAction(PrintMarkClass);
        actionSetMark1->setObjectName(QStringLiteral("actionSetMark1"));
        actionSetMark1->setEnabled(false);
        actionSetMark2 = new QAction(PrintMarkClass);
        actionSetMark2->setObjectName(QStringLiteral("actionSetMark2"));
        actionSetMark2->setEnabled(false);
        actionClear = new QAction(PrintMarkClass);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionClear->setEnabled(false);
        actionRunCpk = new QAction(PrintMarkClass);
        actionRunCpk->setObjectName(QStringLiteral("actionRunCpk"));
        actionSetup = new QAction(PrintMarkClass);
        actionSetup->setObjectName(QStringLiteral("actionSetup"));
        actionSetup->setEnabled(false);
        actionReset = new QAction(PrintMarkClass);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionReset->setEnabled(false);
        actionTest = new QAction(PrintMarkClass);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionGetPos = new QAction(PrintMarkClass);
        actionGetPos->setObjectName(QStringLiteral("actionGetPos"));
        actionGetPos->setEnabled(false);
        actionGoto = new QAction(PrintMarkClass);
        actionGoto->setObjectName(QStringLiteral("actionGoto"));
        actionTGoto = new QAction(PrintMarkClass);
        actionTGoto->setObjectName(QStringLiteral("actionTGoto"));
        actionTrans = new QAction(PrintMarkClass);
        actionTrans->setObjectName(QStringLiteral("actionTrans"));
        actionSaveAs = new QAction(PrintMarkClass);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionReadCode = new QAction(PrintMarkClass);
        actionReadCode->setObjectName(QStringLiteral("actionReadCode"));
        actionGotoCenter = new QAction(PrintMarkClass);
        actionGotoCenter->setObjectName(QStringLiteral("actionGotoCenter"));
        actionTestBadMark = new QAction(PrintMarkClass);
        actionTestBadMark->setObjectName(QStringLiteral("actionTestBadMark"));
        actionSfcWin = new QAction(PrintMarkClass);
        actionSfcWin->setObjectName(QStringLiteral("actionSfcWin"));
        actionSfcWin->setEnabled(false);
        actionSfc = new QAction(PrintMarkClass);
        actionSfc->setObjectName(QStringLiteral("actionSfc"));
        actionSfc->setCheckable(true);
        actionMaintain1 = new QAction(PrintMarkClass);
        actionMaintain1->setObjectName(QStringLiteral("actionMaintain1"));
        actionMaintain1->setEnabled(false);
        actionMaintain2 = new QAction(PrintMarkClass);
        actionMaintain2->setObjectName(QStringLiteral("actionMaintain2"));
        actionMaintain2->setEnabled(false);
        actionNew = new QAction(PrintMarkClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionNew->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon3);
        actionNew->setIconVisibleInMenu(true);
        actionink = new QAction(PrintMarkClass);
        actionink->setObjectName(QStringLiteral("actionink"));
        actionArraySetup = new QAction(PrintMarkClass);
        actionArraySetup->setObjectName(QStringLiteral("actionArraySetup"));
        actionMovePosition = new QAction(PrintMarkClass);
        actionMovePosition->setObjectName(QStringLiteral("actionMovePosition"));
        actiondpyBattery = new QAction(PrintMarkClass);
        actiondpyBattery->setObjectName(QStringLiteral("actiondpyBattery"));
        centralWidget = new QWidget(PrintMarkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 69, 551));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_6->addWidget(scrollArea);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 177, 22));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(widget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);
        toolButton->setStyleSheet(QLatin1String("QToolButton {\n"
"	border: 0px solid #8f8f91;\n"
"    border-radius: 1px;\n"
"    background-color: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,\n"
"                                      stop: 0 #aaaaae, stop: 1 #b6b7ba);\n"
"}\n"
"\n"
"QToolButton:checked{\n"
"    background-color: qlineargradient(x1: 0, y1: 1, x2: 0, y2: 0,\n"
"                                      stop: 0 #76f77a, stop: 1 #6adb6e);\n"
"}"));
        toolButton->setCheckable(true);

        horizontalLayout_2->addWidget(toolButton);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(30, 0));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_6);

        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(20, 50, 482, 23));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout_7 = new QHBoxLayout(widget_2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(widget_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(255, 255, 255, 255), stop:0.435 rgba(255, 255, 255, 255), stop:0.436 rgba(255, 0, 0, 64), stop:0.61 rgba(255, 0, 0, 64), stop:0.611 rgba(255, 255, 255, 255), stop:1 rgba(255, 255, 255, 255));"));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(lineEdit_2);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(pushButton_2);

        checkBox_2 = new QCheckBox(widget_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout_7->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(widget_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        horizontalLayout_7->addWidget(checkBox_3);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy2.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(pushButton_3);

        pushButton_12 = new QPushButton(frame);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(100, 150, 106, 23));
        sizePolicy2.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy2);
        pushButton_12->setCheckable(true);
        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(20, 90, 237, 23));
        horizontalLayout_8 = new QHBoxLayout(widget_3);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        pushButton_19 = new QPushButton(widget_3);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setEnabled(false);
        sizePolicy2.setHeightForWidth(pushButton_19->sizePolicy().hasHeightForWidth());
        pushButton_19->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(pushButton_19);

        pushButton_20 = new QPushButton(widget_3);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setEnabled(false);
        sizePolicy2.setHeightForWidth(pushButton_20->sizePolicy().hasHeightForWidth());
        pushButton_20->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(pushButton_20);

        pushButton_21 = new QPushButton(widget_3);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton_21->sizePolicy().hasHeightForWidth());
        pushButton_21->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(pushButton_21);

        pushButton_22 = new QPushButton(frame);
        pushButton_22->setObjectName(QStringLiteral("pushButton_22"));
        pushButton_22->setGeometry(QRect(190, 280, 75, 23));
        sizePolicy2.setHeightForWidth(pushButton_22->sizePolicy().hasHeightForWidth());
        pushButton_22->setSizePolicy(sizePolicy2);
        checkBox_5 = new QCheckBox(frame);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setEnabled(false);
        checkBox_5->setGeometry(QRect(60, 220, 71, 16));
        sizePolicy2.setHeightForWidth(checkBox_5->sizePolicy().hasHeightForWidth());
        checkBox_5->setSizePolicy(sizePolicy2);
        checkBox_6 = new QCheckBox(frame);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setGeometry(QRect(60, 260, 91, 19));
        checkBox_7 = new QCheckBox(frame);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setGeometry(QRect(60, 290, 91, 19));
        pushButton_14 = new QPushButton(frame);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setEnabled(false);
        pushButton_14->setGeometry(QRect(60, 190, 55, 23));
        sizePolicy2.setHeightForWidth(pushButton_14->sizePolicy().hasHeightForWidth());
        pushButton_14->setSizePolicy(sizePolicy2);
        pushButton_17 = new QPushButton(frame);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setEnabled(false);
        pushButton_17->setGeometry(QRect(60, 350, 57, 23));
        sizePolicy2.setHeightForWidth(pushButton_17->sizePolicy().hasHeightForWidth());
        pushButton_17->setSizePolicy(sizePolicy2);
        checkBox_8 = new QCheckBox(frame);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setGeometry(QRect(60, 320, 91, 19));
        pushButton_23 = new QPushButton(frame);
        pushButton_23->setObjectName(QStringLiteral("pushButton_23"));
        pushButton_23->setGeometry(QRect(180, 180, 93, 28));
        comboBox_2 = new QComboBox(frame);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 390, 87, 31));
        pushButton_24 = new QPushButton(frame);
        pushButton_24->setObjectName(QStringLiteral("pushButton_24"));
        pushButton_24->setGeometry(QRect(160, 390, 93, 28));
        checkBox_9 = new QCheckBox(frame);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setGeometry(QRect(170, 320, 91, 19));
        pushButton_13 = new QPushButton(frame);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setEnabled(false);
        pushButton_13->setGeometry(QRect(180, 500, 108, 23));
        pushButton_13->setCheckable(true);

        horizontalLayout_6->addWidget(frame);

        horizontalLayout_6->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_6, 0, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_3->addWidget(pushButton_4, 0, 0, 1, 1);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_3->addWidget(pushButton_5, 0, 2, 1, 1);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setEnabled(true);

        gridLayout_3->addWidget(pushButton_6, 0, 3, 1, 1);

        pushButton_18 = new QPushButton(groupBox_2);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));

        gridLayout_3->addWidget(pushButton_18, 1, 0, 1, 1);

        pushButton_15 = new QPushButton(groupBox_2);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));

        gridLayout_3->addWidget(pushButton_15, 1, 2, 1, 1);

        pushButton_25 = new QPushButton(groupBox_2);
        pushButton_25->setObjectName(QStringLiteral("pushButton_25"));

        gridLayout_3->addWidget(pushButton_25, 1, 3, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_9->addWidget(label_14);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(lineEdit);

        checkBox = new QCheckBox(groupBox_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(false);

        horizontalLayout_9->addWidget(checkBox);

        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(false);

        horizontalLayout_9->addWidget(comboBox);

        checkBox_4 = new QCheckBox(groupBox_3);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setEnabled(false);

        horizontalLayout_9->addWidget(checkBox_4);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        toolButton_2 = new QToolButton(groupBox_3);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(toolButton_2);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setMinimumSize(QSize(120, 0));
        label_4->setFrameShape(QFrame::WinPanel);
        label_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(label_4);


        horizontalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        toolButton_3 = new QToolButton(groupBox_3);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(toolButton_3);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setMinimumSize(QSize(120, 0));
        label_5->setFrameShape(QFrame::WinPanel);
        label_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(label_5);


        horizontalLayout->addLayout(horizontalLayout_4);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        tableWidget_3 = new QTableWidget(groupBox_3);
        if (tableWidget_3->columnCount() < 5)
            tableWidget_3->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget_3->rowCount() < 1)
            tableWidget_3->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_3->setItem(0, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem6->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget_3->setItem(0, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget_3->setItem(0, 2, __qtablewidgetitem7);
        QBrush brush(QColor(224, 224, 224, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem8->setBackground(brush);
        tableWidget_3->setItem(0, 3, __qtablewidgetitem8);
        QBrush brush1(QColor(224, 224, 244, 255));
        brush1.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem9->setBackground(brush1);
        tableWidget_3->setItem(0, 4, __qtablewidgetitem9);
        tableWidget_3->setObjectName(QStringLiteral("tableWidget_3"));
        tableWidget_3->setMaximumSize(QSize(16777215, 65));
        tableWidget_3->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_3->setAlternatingRowColors(true);
        tableWidget_3->horizontalHeader()->setDefaultSectionSize(65);
        tableWidget_3->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout->addWidget(tableWidget_3);

        tableWidget_2 = new QTableWidget(groupBox_3);
        if (tableWidget_2->columnCount() < 5)
            tableWidget_2->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_2->setAlternatingRowColors(true);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(65);
        tableWidget_2->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout->addWidget(tableWidget_2);

        tableWidget = new QTableWidget(groupBox_3);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem21);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setDefaultSectionSize(65);
        tableWidget->verticalHeader()->setDefaultSectionSize(21);

        verticalLayout->addWidget(tableWidget);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(pushButton_7, 0, 1, 1, 1);

        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(pushButton_9, 0, 3, 1, 1);

        pushButton_16 = new QPushButton(groupBox_3);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        sizePolicy4.setHeightForWidth(pushButton_16->sizePolicy().hasHeightForWidth());
        pushButton_16->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(pushButton_16, 0, 5, 1, 1);

        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout_2->addWidget(pushButton_11, 0, 6, 1, 1);

        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(pushButton_8, 0, 2, 1, 1);

        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(pushButton_10, 0, 4, 1, 1);

        pushButton_26 = new QPushButton(groupBox_3);
        pushButton_26->setObjectName(QStringLiteral("pushButton_26"));

        gridLayout_2->addWidget(pushButton_26, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);

        verticalLayout_2->addWidget(groupBox_3);


        gridLayout->addLayout(verticalLayout_2, 0, 3, 2, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_3->addWidget(label_7);

        listWidget_2 = new QListWidget(centralWidget);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/signal-attention.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/signal-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget_2);
        __qlistwidgetitem1->setIcon(icon5);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setStyleSheet(QLatin1String("alternate-background-color: rgb(187, 179, 211);\n"
"font: 14pt \"Microsoft YaHei UI\";"));
        listWidget_2->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(listWidget_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lcdNumber_3 = new QLCDNumber(groupBox);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setMinimumSize(QSize(0, 49));
        lcdNumber_3->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);background-color: rgb(255, 255, 255);"));
        lcdNumber_3->setDigitCount(6);

        gridLayout_4->addWidget(lcdNumber_3, 2, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lcdNumber = new QLCDNumber(groupBox);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(0, 49));
        lcdNumber->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);background-color: rgb(255, 255, 255);"));
        lcdNumber->setDigitCount(6);

        gridLayout_4->addWidget(lcdNumber, 0, 1, 1, 1);

        lcdNumber_2 = new QLCDNumber(groupBox);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setMinimumSize(QSize(0, 50));
        lcdNumber_2->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);background-color: rgb(255, 255, 255);"));
        lcdNumber_2->setDigitCount(6);

        gridLayout_4->addWidget(lcdNumber_2, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        gridLayout_4->setColumnStretch(1, 1);

        verticalLayout_3->addWidget(groupBox);

        verticalLayout_3->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout_3, 0, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout_5->addWidget(listWidget);

        horizontalLayout_5->setStretch(0, 1);

        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 2);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        PrintMarkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PrintMarkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1131, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_S = new QMenu(menuBar);
        menu_S->setObjectName(QStringLiteral("menu_S"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        menu_P = new QMenu(menuBar);
        menu_P->setObjectName(QStringLiteral("menu_P"));
        menu_D = new QMenu(menuBar);
        menu_D->setObjectName(QStringLiteral("menu_D"));
        PrintMarkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PrintMarkClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(24, 24));
        PrintMarkClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PrintMarkClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PrintMarkClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_S->menuAction());
        menuBar->addAction(menu_P->menuAction());
        menuBar->addAction(menu_D->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(actionNew);
        menu_F->addAction(actionLoad);
        menu_F->addAction(actionSave);
        menu_F->addAction(actionSaveAs);
        menu_F->addSeparator();
        menu_F->addSeparator();
        menu_F->addAction(actionQuit);
        menu_S->addAction(actionIoPane);
        menu_S->addAction(actionRunParams);
        menu_S->addSeparator();
        menu_S->addAction(actionSfcWin);
        menu_S->addAction(actionSfc);
        menu_S->addAction(actiondpyBattery);
        menu_H->addAction(actionAbout);
        menu_P->addAction(actionReadCode);
        menu_P->addAction(actionGotoCenter);
        menu_P->addAction(actionTestBadMark);
        menu_P->addAction(actionink);
        menu_D->addAction(actionMaintain1);
        menu_D->addAction(actionMaintain2);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionLoad);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();

        retranslateUi(PrintMarkClass);
        QObject::connect(checkBox, SIGNAL(clicked(bool)), tableWidget_2, SLOT(setVisible(bool)));
        QObject::connect(toolButton, SIGNAL(clicked(bool)), horizontalSlider, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(PrintMarkClass);
    } // setupUi

    void retranslateUi(QMainWindow *PrintMarkClass)
    {
        PrintMarkClass->setWindowTitle(QApplication::translate("PrintMarkClass", "\350\207\252\345\212\250\345\226\267\347\240\201\347\263\273\347\273\237", nullptr));
        actionQuit->setText(QApplication::translate("PrintMarkClass", "\351\200\200\345\207\272(&Q)", nullptr));
        actionAbout->setText(QApplication::translate("PrintMarkClass", "\345\205\263\344\272\216(&A)", nullptr));
        actionIoPane->setText(QApplication::translate("PrintMarkClass", "IO\347\233\221\347\244\272(&I)", nullptr));
        actionSysSetup->setText(QApplication::translate("PrintMarkClass", "\347\263\273\347\273\237\345\217\202\346\225\260(&S)", nullptr));
        actionRunParams->setText(QApplication::translate("PrintMarkClass", "\350\277\220\350\241\214\345\217\202\346\225\260(&R)", nullptr));
        actionCamCalib->setText(QApplication::translate("PrintMarkClass", "\347\233\270\346\234\272\346\240\241\345\207\206(&C)", nullptr));
        actionOffsetSetup->setText(QApplication::translate("PrintMarkClass", "\345\201\217\347\247\273\350\256\276\347\275\256(&O)", nullptr));
        actionLoad->setText(QApplication::translate("PrintMarkClass", "\350\275\275\345\205\245\346\226\271\346\241\210(&O)", nullptr));
        actionSave->setText(QApplication::translate("PrintMarkClass", "\344\277\235\345\255\230\346\226\271\346\241\210(&S)", nullptr));
        actionSetMark1->setText(QApplication::translate("PrintMarkClass", "\350\256\276\344\270\272\345\237\272\345\207\2061", nullptr));
        actionSetMark2->setText(QApplication::translate("PrintMarkClass", "\350\256\276\344\270\272\345\237\272\345\207\2062", nullptr));
        actionClear->setText(QApplication::translate("PrintMarkClass", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        actionRunCpk->setText(QApplication::translate("PrintMarkClass", "\350\277\220\350\241\214C&pk", nullptr));
        actionSetup->setText(QApplication::translate("PrintMarkClass", "\350\256\276\347\275\256", nullptr));
        actionReset->setText(QApplication::translate("PrintMarkClass", "\351\207\215\347\275\256", nullptr));
        actionTest->setText(QApplication::translate("PrintMarkClass", "\345\256\232\344\275\215", nullptr));
        actionGetPos->setText(QApplication::translate("PrintMarkClass", "\350\216\267\345\217\226(&G)", nullptr));
        actionGoto->setText(QApplication::translate("PrintMarkClass", "\345\216\273\345\210\260(&T)", nullptr));
        actionTGoto->setText(QApplication::translate("PrintMarkClass", "\345\226\267\347\240\201\345\244\264\345\216\273\345\210\260(&N)", nullptr));
        actionTrans->setText(QApplication::translate("PrintMarkClass", "\350\256\241\347\256\227X'Y'", nullptr));
        actionSaveAs->setText(QApplication::translate("PrintMarkClass", "\345\217\246\345\255\230\346\226\271\346\241\210\344\270\272(&A)", nullptr));
        actionReadCode->setText(QApplication::translate("PrintMarkClass", "\350\257\273\345\217\226\344\272\214\347\273\264\347\240\201(&R)", nullptr));
        actionGotoCenter->setText(QApplication::translate("PrintMarkClass", "\345\256\232\344\275\215\346\250\241\346\235\277\344\270\255\345\277\203(&G)", nullptr));
        actionTestBadMark->setText(QApplication::translate("PrintMarkClass", "\345\235\217\347\202\271\346\265\213\350\257\225(&T)", nullptr));
        actionSfcWin->setText(QApplication::translate("PrintMarkClass", "SFC\347\252\227\345\217\243", nullptr));
        actionSfc->setText(QApplication::translate("PrintMarkClass", "\345\220\257\347\224\250SFC", nullptr));
        actionMaintain1->setText(QApplication::translate("PrintMarkClass", "\344\277\235\345\205\273\345\274\200\345\247\213", nullptr));
        actionMaintain2->setText(QApplication::translate("PrintMarkClass", "\344\277\235\345\205\273\347\273\223\346\235\237", nullptr));
        actionNew->setText(QApplication::translate("PrintMarkClass", "\346\226\260\345\273\272\346\226\271\346\241\210(&N)", nullptr));
        actionink->setText(QApplication::translate("PrintMarkClass", "\345\226\267\347\240\201\345\217\202\346\225\260", nullptr));
        actionArraySetup->setText(QApplication::translate("PrintMarkClass", "\351\230\265\345\210\227", nullptr));
        actionMovePosition->setText(QApplication::translate("PrintMarkClass", "\346\211\271\351\207\217\345\201\217\347\247\273", nullptr));
        actiondpyBattery->setText(QApplication::translate("PrintMarkClass", "\347\224\265\351\207\217\347\233\221\346\216\247", nullptr));
#ifndef QT_NO_TOOLTIP
        actiondpyBattery->setToolTip(QApplication::translate("PrintMarkClass", "\347\224\265\351\207\217\347\233\221\346\216\247", nullptr));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("PrintMarkClass", "\350\203\214\346\231\257\347\201\257", nullptr));
        label_6->setText(QApplication::translate("PrintMarkClass", "0", nullptr));
        lineEdit_2->setText(QApplication::translate("PrintMarkClass", "F0P54S0001FY9Y9Z1", nullptr));
        pushButton->setText(QApplication::translate("PrintMarkClass", "\345\226\267\347\240\201", nullptr));
        pushButton_2->setText(QApplication::translate("PrintMarkClass", "\344\270\213\344\270\200\344\270\252", nullptr));
        checkBox_2->setText(QApplication::translate("PrintMarkClass", "\351\242\240\345\200\222", nullptr));
        checkBox_3->setText(QApplication::translate("PrintMarkClass", "\345\217\215\345\220\221", nullptr));
        pushButton_3->setText(QApplication::translate("PrintMarkClass", "\350\257\273\345\217\226\344\272\214\347\273\264\347\240\201", nullptr));
        pushButton_12->setText(QApplication::translate("PrintMarkClass", "\347\256\241\347\220\206\345\221\230", nullptr));
        pushButton_19->setText(QApplication::translate("PrintMarkClass", "\350\277\233\346\235\277", nullptr));
        pushButton_20->setText(QApplication::translate("PrintMarkClass", "\345\207\272\346\235\277", nullptr));
        pushButton_21->setText(QApplication::translate("PrintMarkClass", "\351\207\215\347\275\256", nullptr));
        pushButton_22->setText(QApplication::translate("PrintMarkClass", "\346\227\266\351\227\264\350\256\260\345\275\225", nullptr));
        checkBox_5->setText(QApplication::translate("PrintMarkClass", "\344\275\234\347\202\272\346\212\225\345\205\245\347\253\231", nullptr));
        checkBox_6->setText(QApplication::translate("PrintMarkClass", "\345\220\214\350\277\233\345\220\214\345\207\272", nullptr));
        checkBox_7->setText(QApplication::translate("PrintMarkClass", "\351\207\215\347\240\201\350\255\246\346\212\245", nullptr));
        pushButton_14->setText(QApplication::translate("PrintMarkClass", "\345\217\221\351\200\201", nullptr));
        pushButton_17->setText(QApplication::translate("PrintMarkClass", "\346\270\205\351\230\237\345\210\227", nullptr));
        checkBox_8->setText(QApplication::translate("PrintMarkClass", "\347\203\244\346\234\272\346\265\213\350\257\225", nullptr));
        pushButton_23->setText(QApplication::translate("PrintMarkClass", "\345\210\235\345\247\213\345\214\226", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254001", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254002", nullptr));
        comboBox_2->setItemText(2, QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254003", nullptr));
        comboBox_2->setItemText(3, QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254004", nullptr));
        comboBox_2->setItemText(4, QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254005", nullptr));

        pushButton_24->setText(QApplication::translate("PrintMarkClass", "\344\277\256\346\224\271\346\226\207\346\234\254", nullptr));
        checkBox_9->setText(QApplication::translate("PrintMarkClass", "\345\217\226\346\266\210\351\200\232\350\256\257", nullptr));
        pushButton_13->setText(QApplication::translate("PrintMarkClass", "\347\233\264\351\200\232\346\250\241\345\274\217", nullptr));
        groupBox_2->setTitle(QApplication::translate("PrintMarkClass", "\350\277\220\350\241\214", nullptr));
        pushButton_4->setText(QApplication::translate("PrintMarkClass", "\345\274\200\345\247\213", nullptr));
        pushButton_5->setText(QApplication::translate("PrintMarkClass", "\345\201\234\346\255\242", nullptr));
        pushButton_6->setText(QApplication::translate("PrintMarkClass", "\344\274\240\351\200\201\345\270\246", nullptr));
        pushButton_18->setText(QApplication::translate("PrintMarkClass", "\346\232\202\345\201\234", nullptr));
        pushButton_15->setText(QApplication::translate("PrintMarkClass", "\346\270\205\351\231\244\346\212\245\350\255\246", nullptr));
        pushButton_25->setText(QApplication::translate("PrintMarkClass", "\345\257\274\350\275\250\350\260\203\345\256\275", nullptr));
        groupBox_3->setTitle(QApplication::translate("PrintMarkClass", "\346\225\260\346\215\256\345\210\227\350\241\250", nullptr));
        label_14->setText(QApplication::translate("PrintMarkClass", "\345\267\245\345\215\225\345\217\267", nullptr));
        checkBox->setText(QString());
        comboBox->setItemText(0, QApplication::translate("PrintMarkClass", "\345\235\217\347\202\271", nullptr));
        comboBox->setItemText(1, QApplication::translate("PrintMarkClass", "\345\235\217\347\202\271+\347\231\275\346\262\271", nullptr));

        checkBox_4->setText(QApplication::translate("PrintMarkClass", "\346\211\253\347\240\201", nullptr));
        toolButton_2->setText(QApplication::translate("PrintMarkClass", "\345\237\272\345\207\2061", nullptr));
        label_4->setText(QApplication::translate("PrintMarkClass", "0.000 0.000 0.000", nullptr));
        toolButton_3->setText(QApplication::translate("PrintMarkClass", "\345\237\272\345\207\2062", nullptr));
        label_5->setText(QApplication::translate("PrintMarkClass", "0.000 0.000 0.000", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PrintMarkClass", "\346\262\273\345\205\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PrintMarkClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PrintMarkClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PrintMarkClass", "X\342\200\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("PrintMarkClass", "Y\342\200\231", nullptr));

        const bool __sortingEnabled = tableWidget_3->isSortingEnabled();
        tableWidget_3->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_3->item(0, 1);
        ___qtablewidgetitem5->setText(QApplication::translate("PrintMarkClass", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_3->item(0, 2);
        ___qtablewidgetitem6->setText(QApplication::translate("PrintMarkClass", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_3->item(0, 3);
        ___qtablewidgetitem7->setText(QApplication::translate("PrintMarkClass", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_3->item(0, 4);
        ___qtablewidgetitem8->setText(QApplication::translate("PrintMarkClass", "0", nullptr));
        tableWidget_3->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("PrintMarkClass", "\345\235\217\347\202\271", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("PrintMarkClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("PrintMarkClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("PrintMarkClass", "X\342\200\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("PrintMarkClass", "Y\342\200\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QApplication::translate("PrintMarkClass", "\345\226\267\347\240\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QApplication::translate("PrintMarkClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QApplication::translate("PrintMarkClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem17->setText(QApplication::translate("PrintMarkClass", "X\342\200\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem18->setText(QApplication::translate("PrintMarkClass", "Y\342\200\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem19->setText(QApplication::translate("PrintMarkClass", "U", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem20->setText(QApplication::translate("PrintMarkClass", "\346\226\207\346\234\254\351\200\211\346\213\251", nullptr));
        pushButton_7->setText(QApplication::translate("PrintMarkClass", "\346\267\273\345\212\240", nullptr));
        pushButton_9->setText(QApplication::translate("PrintMarkClass", "\344\270\212\347\247\273", nullptr));
        pushButton_16->setText(QApplication::translate("PrintMarkClass", "\345\205\250\351\200\211", nullptr));
        pushButton_11->setText(QApplication::translate("PrintMarkClass", "\345\205\266\344\273\226", nullptr));
        pushButton_8->setText(QApplication::translate("PrintMarkClass", "\345\210\240\351\231\244", nullptr));
        pushButton_10->setText(QApplication::translate("PrintMarkClass", "\344\270\213\347\247\273", nullptr));
        pushButton_26->setText(QApplication::translate("PrintMarkClass", "12", nullptr));
        label_7->setText(QApplication::translate("PrintMarkClass", "\346\225\205\351\232\234\345\210\227\350\241\250", nullptr));

        const bool __sortingEnabled1 = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_2->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("PrintMarkClass", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_2->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("PrintMarkClass", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        listWidget_2->setSortingEnabled(__sortingEnabled1);

        groupBox->setTitle(QApplication::translate("PrintMarkClass", "\345\226\267\347\240\201\347\273\237\350\256\241", nullptr));
        label->setText(QApplication::translate("PrintMarkClass", "\346\200\273\350\256\241\347\224\237\344\272\247\346\225\260\351\207\217", nullptr));
        label_2->setText(QApplication::translate("PrintMarkClass", "\347\233\256\345\211\215\347\224\237\344\272\247\346\225\260\351\207\217", nullptr));
        label_3->setText(QApplication::translate("PrintMarkClass", "\345\211\251\344\275\231\346\225\260\351\207\217", nullptr));
        menu_F->setTitle(QApplication::translate("PrintMarkClass", "\346\226\207\344\273\266(&F)", nullptr));
        menu_S->setTitle(QApplication::translate("PrintMarkClass", "\347\263\273\347\273\237(&S)", nullptr));
        menu_H->setTitle(QApplication::translate("PrintMarkClass", "\345\270\256\345\212\251(&H)", nullptr));
        menu_P->setTitle(QApplication::translate("PrintMarkClass", "\346\223\215\344\275\234(&P)", nullptr));
        menu_D->setTitle(QApplication::translate("PrintMarkClass", "\350\256\276\345\244\207(&D)", nullptr));
        mainToolBar->setWindowTitle(QApplication::translate("PrintMarkClass", "\345\267\245\345\205\267\346\240\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrintMarkClass: public Ui_PrintMarkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTMARK_H
