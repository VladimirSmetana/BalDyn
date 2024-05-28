/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_exit;
    QAction *action_6;
    QAction *action_5;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QWidget *centralwidget;
    QCustomPlot *widget;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLabel *label_12;
    QLabel *label_13;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_9;
    QLineEdit *lineEdit_7;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_6;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_10;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_8;
    QLabel *label_14;
    QLineEdit *lineEdit_12;
    QLabel *label_15;
    QLineEdit *lineEdit_13;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *height_Button;
    QPushButton *trj_Button;
    QPushButton *distance_Button;
    QPushButton *velocity_Button;
    QPushButton *alpha_Button;
    QPushButton *T_angle_Button;
    QPushButton *Q_Button;
    QPushButton *center_Button;
    QPushButton *thrust_Button;
    QPushButton *mass_Button;
    QPushButton *NX_Button;
    QPushButton *fokus_Button;
    QPushButton *static_Button;
    QPushButton *YZmoment_Button;
    QPushButton *Xmoment_Button;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *height_Button_3;
    QPushButton *height_Button_4;
    QPushButton *height_Button_2;
    QPushButton *pushButton;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1271, 650);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:  rgb(235, 237, 255);\n"
"color: black;"));
        action = new QAction(MainWindow);
        action->setObjectName("action");
        action_2 = new QAction(MainWindow);
        action_2->setObjectName("action_2");
        action_2->setEnabled(false);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName("action_3");
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName("action_exit");
        action_6 = new QAction(MainWindow);
        action_6->setObjectName("action_6");
        action_6->setEnabled(false);
        action_5 = new QAction(MainWindow);
        action_5->setObjectName("action_5");
        action_7 = new QAction(MainWindow);
        action_7->setObjectName("action_7");
        action_8 = new QAction(MainWindow);
        action_8->setObjectName("action_8");
        action_9 = new QAction(MainWindow);
        action_9->setObjectName("action_9");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(590, 80, 381, 281));
        QFont font;
        font.setUnderline(false);
        widget->setFont(font);
        widget->setToolTipDuration(0);
        widget->setStyleSheet(QString::fromUtf8(""));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 30, 271, 171));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(133, 172, 255);\n"
"color: rgb(118, 0, 2);"));
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(170, 40, 81, 30));
        lineEdit_5->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(170, 70, 81, 30));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 40, 61, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 70, 49, 16));
        lineEdit_10 = new QLineEdit(groupBox);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(170, 100, 81, 30));
        lineEdit_10->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_11 = new QLineEdit(groupBox);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(170, 130, 81, 30));
        lineEdit_11->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 100, 141, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 130, 151, 16));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 210, 271, 401));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(133, 172, 255);\n"
"color: rgb(118, 0, 2);"));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(170, 30, 81, 30));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 161, 20));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(170, 70, 81, 30));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 161, 20));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 110, 161, 20));
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(170, 110, 81, 30));
        lineEdit_7->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label = new QLabel(groupBox_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 190, 161, 20));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(170, 190, 81, 30));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(170, 150, 81, 30));
        lineEdit_6->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 150, 161, 20));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 270, 161, 20));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 230, 161, 20));
        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(170, 270, 81, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(170, 230, 81, 30));
        lineEdit_8->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 350, 161, 20));
        lineEdit_12 = new QLineEdit(groupBox_2);
        lineEdit_12->setObjectName("lineEdit_12");
        lineEdit_12->setGeometry(QRect(170, 350, 81, 31));
        lineEdit_12->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 310, 161, 20));
        lineEdit_13 = new QLineEdit(groupBox_2);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(170, 310, 81, 31));
        lineEdit_13->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(300, 30, 271, 601));
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(133, 172, 255);\n"
"color: black;"));
        groupBox_3->setFlat(false);
        verticalLayoutWidget = new QWidget(groupBox_3);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 30, 241, 541));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        height_Button = new QPushButton(verticalLayoutWidget);
        height_Button->setObjectName("height_Button");
        height_Button->setContextMenuPolicy(Qt::CustomContextMenu);
        height_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));
        height_Button->setCheckable(false);
        height_Button->setAutoRepeat(false);
        height_Button->setAutoExclusive(false);
        height_Button->setAutoDefault(false);

        verticalLayout->addWidget(height_Button);

        trj_Button = new QPushButton(verticalLayoutWidget);
        trj_Button->setObjectName("trj_Button");
        trj_Button->setStyleSheet(QString::fromUtf8("background-color:  rgb(102, 13, 19);\n"
"color: white;\n"
"\n"
""));

        verticalLayout->addWidget(trj_Button);

        distance_Button = new QPushButton(verticalLayoutWidget);
        distance_Button->setObjectName("distance_Button");
        distance_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(distance_Button);

        velocity_Button = new QPushButton(verticalLayoutWidget);
        velocity_Button->setObjectName("velocity_Button");
        velocity_Button->setStyleSheet(QString::fromUtf8("background-color:  rgb(102, 13, 19);\n"
"color: white;\n"
"\n"
""));

        verticalLayout->addWidget(velocity_Button);

        alpha_Button = new QPushButton(verticalLayoutWidget);
        alpha_Button->setObjectName("alpha_Button");
        alpha_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(alpha_Button);

        T_angle_Button = new QPushButton(verticalLayoutWidget);
        T_angle_Button->setObjectName("T_angle_Button");
        T_angle_Button->setStyleSheet(QString::fromUtf8("background-color:  rgb(102, 13, 19);\n"
"color: white;\n"
"\n"
""));

        verticalLayout->addWidget(T_angle_Button);

        Q_Button = new QPushButton(verticalLayoutWidget);
        Q_Button->setObjectName("Q_Button");
        Q_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(Q_Button);

        center_Button = new QPushButton(verticalLayoutWidget);
        center_Button->setObjectName("center_Button");
        center_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(center_Button);

        thrust_Button = new QPushButton(verticalLayoutWidget);
        thrust_Button->setObjectName("thrust_Button");
        thrust_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(thrust_Button);

        mass_Button = new QPushButton(verticalLayoutWidget);
        mass_Button->setObjectName("mass_Button");
        mass_Button->setStyleSheet(QString::fromUtf8("background-color:  rgb(102, 13, 19);\n"
"color: white;\n"
"\n"
"\n"
""));

        verticalLayout->addWidget(mass_Button);

        NX_Button = new QPushButton(verticalLayoutWidget);
        NX_Button->setObjectName("NX_Button");
        NX_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(NX_Button);

        fokus_Button = new QPushButton(verticalLayoutWidget);
        fokus_Button->setObjectName("fokus_Button");
        fokus_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(fokus_Button);

        static_Button = new QPushButton(verticalLayoutWidget);
        static_Button->setObjectName("static_Button");
        static_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(static_Button);

        YZmoment_Button = new QPushButton(verticalLayoutWidget);
        YZmoment_Button->setObjectName("YZmoment_Button");
        YZmoment_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(YZmoment_Button);

        Xmoment_Button = new QPushButton(verticalLayoutWidget);
        Xmoment_Button->setObjectName("Xmoment_Button");
        Xmoment_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout->addWidget(Xmoment_Button);

        lineEdit_14 = new QLineEdit(centralwidget);
        lineEdit_14->setObjectName("lineEdit_14");
        lineEdit_14->setGeometry(QRect(590, 30, 81, 30));
        lineEdit_14->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_15 = new QLineEdit(centralwidget);
        lineEdit_15->setObjectName("lineEdit_15");
        lineEdit_15->setGeometry(QRect(680, 30, 81, 30));
        lineEdit_15->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        lineEdit_16 = new QLineEdit(centralwidget);
        lineEdit_16->setObjectName("lineEdit_16");
        lineEdit_16->setGeometry(QRect(770, 30, 81, 30));
        lineEdit_16->setStyleSheet(QString::fromUtf8("background-color: white ;\n"
"color: rgb(0, 0, 88);"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(990, 20, 271, 601));
        groupBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(133, 172, 255);\n"
"color: black;"));
        groupBox_4->setFlat(false);
        verticalLayoutWidget_2 = new QWidget(groupBox_4);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 30, 241, 541));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        height_Button_3 = new QPushButton(verticalLayoutWidget_2);
        height_Button_3->setObjectName("height_Button_3");
        height_Button_3->setContextMenuPolicy(Qt::CustomContextMenu);
        height_Button_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));
        height_Button_3->setCheckable(false);
        height_Button_3->setAutoRepeat(false);
        height_Button_3->setAutoExclusive(false);
        height_Button_3->setAutoDefault(false);

        verticalLayout_2->addWidget(height_Button_3);

        height_Button_4 = new QPushButton(verticalLayoutWidget_2);
        height_Button_4->setObjectName("height_Button_4");
        height_Button_4->setContextMenuPolicy(Qt::CustomContextMenu);
        height_Button_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));
        height_Button_4->setCheckable(false);
        height_Button_4->setAutoRepeat(false);
        height_Button_4->setAutoExclusive(false);
        height_Button_4->setAutoDefault(false);

        verticalLayout_2->addWidget(height_Button_4);

        height_Button_2 = new QPushButton(verticalLayoutWidget_2);
        height_Button_2->setObjectName("height_Button_2");
        height_Button_2->setContextMenuPolicy(Qt::CustomContextMenu);
        height_Button_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));
        height_Button_2->setCheckable(false);
        height_Button_2->setAutoRepeat(false);
        height_Button_2->setAutoExclusive(false);
        height_Button_2->setAutoDefault(false);

        verticalLayout_2->addWidget(height_Button_2);

        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 88);\n"
"color: white"));

        verticalLayout_2->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1271, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addSeparator();
        menu->addSeparator();
        menu->addSeparator();
        menu->addAction(action_5);
        menu_2->addAction(action_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\265\320\272\321\202\320\275\321\213\320\271 \321\200\320\260\321\201\321\207\320\265\321\202 \320\264\320\262\321\203\321\205\321\201\321\202\321\203\320\277\320\265\320\275\321\207\320\260\321\202\320\276\320\271 \321\200\320\260\320\272\320\265\321\202\321\213", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\273\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\246\320\230\320\245", nullptr));
        action_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\275\320\260\320\274\320\270\320\272\320\260", nullptr));
        action_exit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        action_6->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\273\321\213", nullptr));
        action_5->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\320\275\320\260\320\274\320\270\320\272\320\260", nullptr));
        action_7->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        action_8->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273", nullptr));
        action_9->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\245\320\236\320\224\320\235\320\253\320\225 \320\237\320\220\320\240\320\220\320\234\320\225\320\242\320\240\320\253", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "-4.3", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "0.0344", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\262\320\276\321\200\320\276\321\202", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("MainWindow", "1.7", nullptr));
        lineEdit_11->setText(QCoreApplication::translate("MainWindow", "1.1", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\320\242\321\217\320\263\320\276\320\262\320\276\320\276\321\200\321\203\320\266\320\265\320\275\320\275\320\276\321\201\321\202\321\214 1\320\241\320\242", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\320\242\321\217\320\263\320\276\320\262\320\276\320\276\321\200\321\203\320\266\320\265\320\275\320\275\320\276\321\201\321\202\321\214 2 \320\241\320\242", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\220\320\235\320\235\320\253\320\225 \320\240\320\220\320\241\320\247\320\225\320\242\320\220", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214, \320\274/c", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260, \320\274", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\277\320\276\320\273\320\265\321\202\320\260 \320\234\320\221, \320\274", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \320\277\320\276\320\273\320\265\321\202\320\260 I \321\201\321\202, \321\201", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201 \321\201\320\272\320\276\321\200 \320\275\320\260\320\277\320\276\321\200, \320\272\320\263/\320\274\321\2012", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \321\202\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\320\270 (2), \320\263\321\200\320\260\320\264", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \321\202\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\320\270 (1), \320\263\321\200\320\260\320\264", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275. \321\203\320\263\320\276\320\273 \320\260\321\202\320\260\320\272\320\270, \320\263\321\200\320\260\320\264", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \321\202\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\320\270 (3), \320\263\321\200\320\260\320\264", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\253\320\245\320\236\320\224\320\235\320\253\320\225 \320\237\320\220\320\240\320\220\320\234\320\225\320\242\320\240\320\253", nullptr));
        height_Button->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\260", nullptr));
        trj_Button->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        distance_Button->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\273\321\214\320\275\320\276\321\201\321\202\321\214", nullptr));
        velocity_Button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", nullptr));
        alpha_Button->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \320\260\321\202\320\260\320\272\320\270", nullptr));
        T_angle_Button->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \321\202\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\320\270", nullptr));
        Q_Button->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\320\275\320\276\320\271 \320\275\320\260\320\277\320\276\321\200", nullptr));
        center_Button->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200 \320\274\320\260\321\201\321\201", nullptr));
        thrust_Button->setText(QCoreApplication::translate("MainWindow", "\320\242\321\217\320\263\320\260", nullptr));
        mass_Button->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\201\320\260", nullptr));
        NX_Button->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\321\214\320\275\320\260\321\217 \320\277\320\265\321\200\320\265\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        fokus_Button->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\320\272\321\203\321\201", nullptr));
        static_Button->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202 \320\274\320\276\320\274\320\265\320\275\321\202", nullptr));
        YZmoment_Button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\277\320\265\321\200\320\265\321\207\320\275\321\213\320\271 \321\206\320\265\320\275\321\202\321\200\320\276\320\261\320\265\320\266\320\275\321\213\320\271 \320\274\320\276\320\274\320\265\320\275\321\202", nullptr));
        Xmoment_Button->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\264\320\276\320\273\321\214\320\275\321\213\320\271 \321\206\320\265\320\275\321\202\321\200\320\276\320\261\320\265\320\266\320\275\321\213\320\271 \320\274\320\276\320\274\320\265\320\275\321\202", nullptr));
        lineEdit_14->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_15->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_16->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\230\320\235\320\220\320\234\320\230\320\247\320\225\320\241\320\232\320\230\320\225 \320\237\320\220\320\240\320\220\320\234\320\225\320\242\320\240\320\253", nullptr));
        height_Button_3->setText(QCoreApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260 \320\272\320\276\320\273\320\265\320\261\320\260\320\275\320\270\320\271", nullptr));
        height_Button_4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\275\320\260\321\217 \321\204\320\276\321\200\320\274\321\213 \320\272\320\276\320\273\320\265\320\261\320\260\320\275\320\270\320\271", nullptr));
        height_Button_2->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\321\213 \320\272\320\276\320\273\320\265\320\261\320\260\320\275\320\270\320\271", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\202\320\265\321\200", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
