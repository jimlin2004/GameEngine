/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "EditorOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionsave;
    QAction *actionopen;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    EditorOpenGLWidget *widget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetLeft;
    QWidget *dockWidgetContentsLeft;
    QGridLayout *gridLayout;
    QWidget *wrapWidgetLeft;
    QDockWidget *dockWidgetRight;
    QWidget *dockWidgetContentsRight;
    QGridLayout *gridLayout_3;
    QWidget *wrapWidgetRight;
    QDockWidget *dockWidgetBottom;
    QWidget *dockWidgetContentsBottom;
    QGridLayout *gridLayout_2;
    QWidget *wrapWidgetBottom;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName("actionsave");
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName("actionopen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new EditorOpenGLWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(widget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menubar->setStyleSheet(QString::fromUtf8(""));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuFile->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        dockWidgetLeft = new QDockWidget(MainWindow);
        dockWidgetLeft->setObjectName("dockWidgetLeft");
        dockWidgetLeft->setStyleSheet(QString::fromUtf8(""));
        dockWidgetContentsLeft = new QWidget();
        dockWidgetContentsLeft->setObjectName("dockWidgetContentsLeft");
        dockWidgetContentsLeft->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(dockWidgetContentsLeft);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wrapWidgetLeft = new QWidget(dockWidgetContentsLeft);
        wrapWidgetLeft->setObjectName("wrapWidgetLeft");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wrapWidgetLeft->sizePolicy().hasHeightForWidth());
        wrapWidgetLeft->setSizePolicy(sizePolicy);
        wrapWidgetLeft->setAutoFillBackground(false);
        wrapWidgetLeft->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(wrapWidgetLeft, 0, 0, 1, 1);

        dockWidgetLeft->setWidget(dockWidgetContentsLeft);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidgetLeft);
        dockWidgetRight = new QDockWidget(MainWindow);
        dockWidgetRight->setObjectName("dockWidgetRight");
        dockWidgetRight->setStyleSheet(QString::fromUtf8("color: #ffffff;"));
        dockWidgetContentsRight = new QWidget();
        dockWidgetContentsRight->setObjectName("dockWidgetContentsRight");
        gridLayout_3 = new QGridLayout(dockWidgetContentsRight);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        wrapWidgetRight = new QWidget(dockWidgetContentsRight);
        wrapWidgetRight->setObjectName("wrapWidgetRight");

        gridLayout_3->addWidget(wrapWidgetRight, 0, 0, 1, 1);

        dockWidgetRight->setWidget(dockWidgetContentsRight);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidgetRight);
        dockWidgetBottom = new QDockWidget(MainWindow);
        dockWidgetBottom->setObjectName("dockWidgetBottom");
        dockWidgetBottom->setMinimumSize(QSize(79, 39));
        dockWidgetBottom->setStyleSheet(QString::fromUtf8(""));
        dockWidgetContentsBottom = new QWidget();
        dockWidgetContentsBottom->setObjectName("dockWidgetContentsBottom");
        dockWidgetContentsBottom->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(dockWidgetContentsBottom);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        wrapWidgetBottom = new QWidget(dockWidgetContentsBottom);
        wrapWidgetBottom->setObjectName("wrapWidgetBottom");
        sizePolicy.setHeightForWidth(wrapWidgetBottom->sizePolicy().hasHeightForWidth());
        wrapWidgetBottom->setSizePolicy(sizePolicy);
        wrapWidgetBottom->setAutoFillBackground(false);
        wrapWidgetBottom->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(wrapWidgetBottom, 0, 0, 1, 1);

        dockWidgetBottom->setWidget(dockWidgetContentsBottom);
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidgetBottom);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionsave);
        menuFile->addAction(actionopen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Engine Editor", nullptr));
        actionsave->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        dockWidgetLeft->setWindowTitle(QCoreApplication::translate("MainWindow", "Object information", nullptr));
        dockWidgetRight->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Objects", nullptr));
        dockWidgetBottom->setWindowTitle(QCoreApplication::translate("MainWindow", "Assets", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
