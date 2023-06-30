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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "EditorOpenGLWidget.h"
#include "LineEditFloat.h"
#include "QCollapsibleWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionsave;
    QAction *actionopen;
    QAction *actioncompile;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    EditorOpenGLWidget *openglWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetLeft;
    QWidget *dockWidgetContentsLeft;
    QVBoxLayout *verticalLayout_5;
    QWidget *wrapWidgetLeft;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_detail;
    QWidget *scrollAreaWidgetContents_detail;
    QVBoxLayout *verticalLayout_3;
    QCollapsibleWidget *qCollapsibleWidget_transform;
    QWidget *contentWidget_transform;
    QHBoxLayout *horizontalLayout;
    QLabel *label_x_transform;
    LineEditFloat *lineEditFloat_x_transform;
    QLabel *label_y_transform;
    LineEditFloat *lineEditFloat_y_transform;
    QLabel *label_z_transform;
    LineEditFloat *lineEditFloat_z_transform;
    QCollapsibleWidget *qCollapsibleWidget_scale;
    QWidget *contentWidget_scale;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_x_scale;
    LineEditFloat *lineEditFloat_x_scale;
    QLabel *label_y_scale;
    LineEditFloat *lineEditFloat_y_scale;
    QLabel *label_z_scale;
    LineEditFloat *lineEditFloat_z_scale;
    QCollapsibleWidget *qCollapsibleWidget_color;
    QWidget *contentWidget_color;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_R_color;
    LineEditFloat *lineEditFloat_R_color;
    QLabel *label_G_color;
    LineEditFloat *lineEditFloat_G_color;
    QLabel *label_B_color;
    LineEditFloat *lineEditFloat_B_color;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QWidget *widget_colorViewer;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_colorPicker;
    QSpacerItem *verticalSpacer;
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
        MainWindow->resize(679, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName("actionsave");
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName("actionopen");
        actioncompile = new QAction(MainWindow);
        actioncompile->setObjectName("actioncompile");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/complie.png"), QSize(), QIcon::Normal, QIcon::Off);
        actioncompile->setIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        openglWidget = new EditorOpenGLWidget(centralwidget);
        openglWidget->setObjectName("openglWidget");
        openglWidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(openglWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 679, 22));
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
        verticalLayout_5 = new QVBoxLayout(dockWidgetContentsLeft);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        wrapWidgetLeft = new QWidget(dockWidgetContentsLeft);
        wrapWidgetLeft->setObjectName("wrapWidgetLeft");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wrapWidgetLeft->sizePolicy().hasHeightForWidth());
        wrapWidgetLeft->setSizePolicy(sizePolicy);
        wrapWidgetLeft->setAutoFillBackground(false);
        wrapWidgetLeft->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(wrapWidgetLeft);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea_detail = new QScrollArea(wrapWidgetLeft);
        scrollArea_detail->setObjectName("scrollArea_detail");
        scrollArea_detail->setWidgetResizable(true);
        scrollAreaWidgetContents_detail = new QWidget();
        scrollAreaWidgetContents_detail->setObjectName("scrollAreaWidgetContents_detail");
        scrollAreaWidgetContents_detail->setGeometry(QRect(0, 0, 257, 296));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents_detail->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_detail->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents_detail->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_detail);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        qCollapsibleWidget_transform = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_transform->setObjectName("qCollapsibleWidget_transform");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(qCollapsibleWidget_transform->sizePolicy().hasHeightForWidth());
        qCollapsibleWidget_transform->setSizePolicy(sizePolicy1);
        contentWidget_transform = new QWidget(qCollapsibleWidget_transform);
        contentWidget_transform->setObjectName("contentWidget_transform");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(contentWidget_transform->sizePolicy().hasHeightForWidth());
        contentWidget_transform->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(contentWidget_transform);
        horizontalLayout->setObjectName("horizontalLayout");
        label_x_transform = new QLabel(contentWidget_transform);
        label_x_transform->setObjectName("label_x_transform");

        horizontalLayout->addWidget(label_x_transform);

        lineEditFloat_x_transform = new LineEditFloat(contentWidget_transform);
        lineEditFloat_x_transform->setObjectName("lineEditFloat_x_transform");

        horizontalLayout->addWidget(lineEditFloat_x_transform);

        label_y_transform = new QLabel(contentWidget_transform);
        label_y_transform->setObjectName("label_y_transform");

        horizontalLayout->addWidget(label_y_transform);

        lineEditFloat_y_transform = new LineEditFloat(contentWidget_transform);
        lineEditFloat_y_transform->setObjectName("lineEditFloat_y_transform");

        horizontalLayout->addWidget(lineEditFloat_y_transform);

        label_z_transform = new QLabel(contentWidget_transform);
        label_z_transform->setObjectName("label_z_transform");

        horizontalLayout->addWidget(label_z_transform);

        lineEditFloat_z_transform = new LineEditFloat(contentWidget_transform);
        lineEditFloat_z_transform->setObjectName("lineEditFloat_z_transform");

        horizontalLayout->addWidget(lineEditFloat_z_transform);


        verticalLayout_3->addWidget(qCollapsibleWidget_transform);

        qCollapsibleWidget_scale = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_scale->setObjectName("qCollapsibleWidget_scale");
        contentWidget_scale = new QWidget(qCollapsibleWidget_scale);
        contentWidget_scale->setObjectName("contentWidget_scale");
        sizePolicy2.setHeightForWidth(contentWidget_scale->sizePolicy().hasHeightForWidth());
        contentWidget_scale->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(contentWidget_scale);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_x_scale = new QLabel(contentWidget_scale);
        label_x_scale->setObjectName("label_x_scale");

        horizontalLayout_2->addWidget(label_x_scale);

        lineEditFloat_x_scale = new LineEditFloat(contentWidget_scale);
        lineEditFloat_x_scale->setObjectName("lineEditFloat_x_scale");

        horizontalLayout_2->addWidget(lineEditFloat_x_scale);

        label_y_scale = new QLabel(contentWidget_scale);
        label_y_scale->setObjectName("label_y_scale");

        horizontalLayout_2->addWidget(label_y_scale);

        lineEditFloat_y_scale = new LineEditFloat(contentWidget_scale);
        lineEditFloat_y_scale->setObjectName("lineEditFloat_y_scale");

        horizontalLayout_2->addWidget(lineEditFloat_y_scale);

        label_z_scale = new QLabel(contentWidget_scale);
        label_z_scale->setObjectName("label_z_scale");

        horizontalLayout_2->addWidget(label_z_scale);

        lineEditFloat_z_scale = new LineEditFloat(contentWidget_scale);
        lineEditFloat_z_scale->setObjectName("lineEditFloat_z_scale");

        horizontalLayout_2->addWidget(lineEditFloat_z_scale);


        verticalLayout_3->addWidget(qCollapsibleWidget_scale);

        qCollapsibleWidget_color = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_color->setObjectName("qCollapsibleWidget_color");
        contentWidget_color = new QWidget(qCollapsibleWidget_color);
        contentWidget_color->setObjectName("contentWidget_color");
        sizePolicy2.setHeightForWidth(contentWidget_color->sizePolicy().hasHeightForWidth());
        contentWidget_color->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(contentWidget_color);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_R_color = new QLabel(contentWidget_color);
        label_R_color->setObjectName("label_R_color");

        horizontalLayout_3->addWidget(label_R_color);

        lineEditFloat_R_color = new LineEditFloat(contentWidget_color);
        lineEditFloat_R_color->setObjectName("lineEditFloat_R_color");

        horizontalLayout_3->addWidget(lineEditFloat_R_color);

        label_G_color = new QLabel(contentWidget_color);
        label_G_color->setObjectName("label_G_color");

        horizontalLayout_3->addWidget(label_G_color);

        lineEditFloat_G_color = new LineEditFloat(contentWidget_color);
        lineEditFloat_G_color->setObjectName("lineEditFloat_G_color");

        horizontalLayout_3->addWidget(lineEditFloat_G_color);

        label_B_color = new QLabel(contentWidget_color);
        label_B_color->setObjectName("label_B_color");

        horizontalLayout_3->addWidget(label_B_color);

        lineEditFloat_B_color = new LineEditFloat(contentWidget_color);
        lineEditFloat_B_color->setObjectName("lineEditFloat_B_color");

        horizontalLayout_3->addWidget(lineEditFloat_B_color);


        verticalLayout_4->addLayout(horizontalLayout_3);

        line = new QFrame(contentWidget_color);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(contentWidget_color);
        label->setObjectName("label");

        horizontalLayout_4->addWidget(label);

        widget_colorViewer = new QWidget(contentWidget_color);
        widget_colorViewer->setObjectName("widget_colorViewer");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_colorViewer->sizePolicy().hasHeightForWidth());
        widget_colorViewer->setSizePolicy(sizePolicy3);
        widget_colorViewer->setMinimumSize(QSize(50, 50));

        horizontalLayout_4->addWidget(widget_colorViewer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_colorPicker = new QPushButton(contentWidget_color);
        pushButton_colorPicker->setObjectName("pushButton_colorPicker");

        horizontalLayout_4->addWidget(pushButton_colorPicker);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(qCollapsibleWidget_color);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        scrollArea_detail->setWidget(scrollAreaWidgetContents_detail);

        verticalLayout_2->addWidget(scrollArea_detail);


        verticalLayout_5->addWidget(wrapWidgetLeft);

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
        gridLayout_7->setSpacing(0);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
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
        dockWidgetBottom->setMinimumSize(QSize(145, 179));
        dockWidgetBottom->setStyleSheet(QString::fromUtf8(""));
        dockWidgetContentsBottom = new QWidget();
        dockWidgetContentsBottom->setObjectName("dockWidgetContentsBottom");
        dockWidgetContentsBottom->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(dockWidgetContentsBottom);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 671, 146));
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
        qCollapsibleWidget_transform->setTitle(QCoreApplication::translate("MainWindow", "Tranform", nullptr));
        label_x_transform->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_y_transform->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_z_transform->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        qCollapsibleWidget_scale->setTitle(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        label_x_scale->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_y_scale->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_z_scale->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        qCollapsibleWidget_color->setTitle(QCoreApplication::translate("MainWindow", "Color", nullptr));
        label_R_color->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_G_color->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        label_B_color->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "color", nullptr));
        pushButton_colorPicker->setText(QCoreApplication::translate("MainWindow", "choose color", nullptr));
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
