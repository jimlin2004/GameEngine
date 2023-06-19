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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "EditorOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionsave;
    QAction *actionopen;
    QAction *actioncompile;
    QWidget *centralwidget;
    QGridLayout *gridLayout_6;
    EditorOpenGLWidget *openglWidget;
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
    QGridLayout *gridLayout_7;
    QTreeWidget *treeWidget;
    QDockWidget *dockWidgetBottom;
    QWidget *dockWidgetContentsBottom;
    QGridLayout *gridLayout_2;
    QWidget *wrapWidgetBottom;
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget_manager;
    QWidget *tab_assets;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QToolBar *toolBar;

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
        actioncompile = new QAction(MainWindow);
        actioncompile->setObjectName("actioncompile");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/complieIcon/texture/complie.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncompile->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_6 = new QGridLayout(centralwidget);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        openglWidget = new EditorOpenGLWidget(centralwidget);
        openglWidget->setObjectName("openglWidget");
        openglWidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(openglWidget, 0, 0, 1, 1);

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
        gridLayout_7 = new QGridLayout(wrapWidgetRight);
        gridLayout_7->setObjectName("gridLayout_7");
        treeWidget = new QTreeWidget(wrapWidgetRight);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setColumnCount(1);
        treeWidget->header()->setDefaultSectionSize(60);

        gridLayout_7->addWidget(treeWidget, 0, 0, 1, 1);


        gridLayout_3->addWidget(wrapWidgetRight, 0, 0, 1, 1);

        dockWidgetRight->setWidget(dockWidgetContentsRight);
        MainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidgetRight);
        dockWidgetBottom = new QDockWidget(MainWindow);
        dockWidgetBottom->setObjectName("dockWidgetBottom");
        dockWidgetBottom->setMinimumSize(QSize(145, 167));
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
        gridLayout_5 = new QGridLayout(wrapWidgetBottom);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        tabWidget_manager = new QTabWidget(wrapWidgetBottom);
        tabWidget_manager->setObjectName("tabWidget_manager");
        tab_assets = new QWidget();
        tab_assets->setObjectName("tab_assets");
        gridLayout_4 = new QGridLayout(tab_assets);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(tab_assets);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 792, 229));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget_manager->addTab(tab_assets, QString());
        tab_console = new QWidget();
        tab_console->setObjectName("tab_console");
        verticalLayout = new QVBoxLayout(tab_console);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        textBrowser = new QTextBrowser(tab_console);
        textBrowser->setObjectName("textBrowser");

        verticalLayout->addWidget(textBrowser);

        lineEdit = new QLineEdit(tab_console);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        tabWidget_manager->addTab(tab_console, QString());

        gridLayout_5->addWidget(tabWidget_manager, 0, 0, 1, 1);


        gridLayout_2->addWidget(wrapWidgetBottom, 0, 0, 1, 1);

        dockWidgetBottom->setWidget(dockWidgetContentsBottom);
        MainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidgetBottom);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionsave);
        menuFile->addAction(actionopen);
        toolBar->addAction(actioncompile);

        retranslateUi(MainWindow);

        tabWidget_manager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Engine Editor", nullptr));
        actionsave->setText(QCoreApplication::translate("MainWindow", "save", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        actioncompile->setText(QCoreApplication::translate("MainWindow", "compile", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        dockWidgetLeft->setWindowTitle(QCoreApplication::translate("MainWindow", "Object information", nullptr));
        dockWidgetRight->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Objects", nullptr));
        dockWidgetBottom->setWindowTitle(QCoreApplication::translate("MainWindow", "Manager", nullptr));
        tabWidget_manager->setTabText(tabWidget_manager->indexOf(tab_assets), QCoreApplication::translate("MainWindow", "Assets", nullptr));
        tabWidget_manager->setTabText(tabWidget_manager->indexOf(tab_console), QCoreApplication::translate("MainWindow", "Console", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
