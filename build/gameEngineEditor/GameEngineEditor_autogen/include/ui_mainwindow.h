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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "AdvancedComboBox.h"
#include "ContentBrowserPanel.h"
#include "LineEditFloat.h"
#include "LineEditRotation.h"
#include "OutlineTreeWidget.h"
#include "QCollapsibleWidget.h"
#include "Titlebar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *toolbarLayout;
    QWidget *SDL_windgetWrap;
    QHBoxLayout *horizontalLayout_5;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetLeft;
    QWidget *dockWidgetContentsLeft;
    QVBoxLayout *verticalLayout_5;
    QWidget *wrapWidgetLeft;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea_detail;
    QWidget *scrollAreaWidgetContents_detail;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_addComponentWrap;
    QVBoxLayout *verticalLayout_9;
    QCollapsibleWidget *qCollapsibleWidget_tag;
    QWidget *contentWidget_tag;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_tag;
    QLineEdit *lineEdit_tag;
    QCollapsibleWidget *qCollapsibleWidget_transform;
    QWidget *contentWidget_transform;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_position;
    QHBoxLayout *horizontalLayout_position;
    QLabel *label_x_position;
    LineEditFloat *lineEditFloat_x_position;
    QLabel *label_y_position;
    LineEditFloat *lineEditFloat_y_position;
    QLabel *label_z_position;
    LineEditFloat *lineEditFloat_z_position;
    QFrame *line_2;
    QLabel *label_scale;
    QHBoxLayout *horizontalLayout_scale;
    QLabel *label_x_scale;
    LineEditFloat *lineEditFloat_x_scale;
    QLabel *label_y_scale;
    LineEditFloat *lineEditFloat_y_scale;
    QLabel *label_z_scale;
    LineEditFloat *lineEditFloat_z_scale;
    QFrame *line_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_rotation;
    QLabel *label_x_rotation;
    LineEditRotation *lineEditFloat_x_rotation;
    QLabel *label_y_rotation;
    LineEditRotation *lineEditFloat_y_rotation;
    QLabel *label_z_rotation;
    LineEditRotation *lineEditFloat_z_rotation;
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
    QCollapsibleWidget *qCollapsibleWidget_texture;
    QWidget *contentWidget_texture;
    QHBoxLayout *horizontalLayout;
    QLabel *label_textureViewer;
    AdvancedComboBox *comboBox_texture;
    QSpacerItem *horizontalSpacer_2;
    QCollapsibleWidget *qCollapsibleWidget_camera;
    QWidget *contentWidget_camera;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_isPrimary;
    QCheckBox *checkBox_isPrimary;
    QSpacerItem *horizontalSpacer_4;
    QCollapsibleWidget *qCollapsibleWidget_script;
    QWidget *contentWidget_script;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_script;
    AdvancedComboBox *comboBox_script;
    QSpacerItem *horizontalSpacer_7;
    QCollapsibleWidget *qCollapsibleWidget_rigidbody2D;
    QWidget *contentWidget_rigidbody2D;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_bodyType;
    QComboBox *comboBox_bodyType;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_fixedRotation;
    QCheckBox *checkBox_fixedRotation;
    QSpacerItem *horizontalSpacer_6;
    QCollapsibleWidget *qCollapsibleWidget_boxCollider2D;
    QWidget *contentWidget_boxCollider2D;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_boxCollider2D_offset;
    QHBoxLayout *horizontalLayout_boxCollider2D_offset;
    QLabel *label_boxCollider2D_offset_x;
    LineEditFloat *lineEditFloat_boxCollider2D_offset_x;
    QLabel *label_boxCollider2D_offset_y;
    LineEditFloat *lineEditFloat_boxCollider2D_offset_y;
    QLabel *label_boxCollider2D_size;
    QHBoxLayout *horizontalLayout_boxCollider2D_size;
    QLabel *label_boxCollider2D_size_x;
    LineEditFloat *lineEditFloat_boxCollider2D_size_x;
    QLabel *label_boxCollider2D_size_y;
    LineEditFloat *lineEditFloat_boxCollider2D_size_y;
    QFormLayout *formLayout;
    QLabel *label_boxCollider2D_density;
    LineEditFloat *lineEditFloat_boxCollider2D_density;
    QLabel *label_boxCollider2D_friction;
    LineEditFloat *lineEditFloat_boxCollider2D_friction;
    QLabel *label_boxCollider2D_restitution;
    QLabel *label_boxCollider2D_restitutionThreshold;
    LineEditFloat *lineEditFloat_boxCollider2D_restitution;
    LineEditFloat *lineEditFloat_boxCollider2D_restitutionThreshold;
    QSpacerItem *verticalSpacer;
    QDockWidget *dockWidgetRight;
    QWidget *dockWidgetContentsRight;
    QGridLayout *gridLayout_3;
    QWidget *wrapWidgetRight;
    QGridLayout *gridLayout_7;
    OutlineTreeWidget *treeWidget;
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
    QGridLayout *gridLayout_6;
    ContentBrowserPanel *contentBrowserPanel;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    Titlebar *titlebar;
    QWidget *titlebarContents;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *titlebarLayout;
    QLabel *label_windowIcon;
    QLabel *label_windowTitle;
    QHBoxLayout *menubarLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_minimize;
    QPushButton *pushButton_expand;
    QPushButton *pushButton_close;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(820, 605);
        MainWindow->setMouseTracking(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setObjectName("toolbarLayout");

        verticalLayout_7->addLayout(toolbarLayout);

        SDL_windgetWrap = new QWidget(centralwidget);
        SDL_windgetWrap->setObjectName("SDL_windgetWrap");
        horizontalLayout_5 = new QHBoxLayout(SDL_windgetWrap);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);

        verticalLayout_7->addWidget(SDL_windgetWrap);

        MainWindow->setCentralWidget(centralwidget);
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
        scrollAreaWidgetContents_detail->setGeometry(QRect(0, 0, 454, 981));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents_detail->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_detail->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents_detail->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_detail);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_addComponentWrap = new QWidget(scrollAreaWidgetContents_detail);
        widget_addComponentWrap->setObjectName("widget_addComponentWrap");
        verticalLayout_9 = new QVBoxLayout(widget_addComponentWrap);
        verticalLayout_9->setObjectName("verticalLayout_9");

        verticalLayout_3->addWidget(widget_addComponentWrap);

        qCollapsibleWidget_tag = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_tag->setObjectName("qCollapsibleWidget_tag");
        contentWidget_tag = new QWidget(qCollapsibleWidget_tag);
        contentWidget_tag->setObjectName("contentWidget_tag");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(contentWidget_tag->sizePolicy().hasHeightForWidth());
        contentWidget_tag->setSizePolicy(sizePolicy1);
        horizontalLayout_9 = new QHBoxLayout(contentWidget_tag);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_tag = new QLabel(contentWidget_tag);
        label_tag->setObjectName("label_tag");

        horizontalLayout_9->addWidget(label_tag);

        lineEdit_tag = new QLineEdit(contentWidget_tag);
        lineEdit_tag->setObjectName("lineEdit_tag");

        horizontalLayout_9->addWidget(lineEdit_tag);


        verticalLayout_3->addWidget(qCollapsibleWidget_tag);

        qCollapsibleWidget_transform = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_transform->setObjectName("qCollapsibleWidget_transform");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(qCollapsibleWidget_transform->sizePolicy().hasHeightForWidth());
        qCollapsibleWidget_transform->setSizePolicy(sizePolicy2);
        contentWidget_transform = new QWidget(qCollapsibleWidget_transform);
        contentWidget_transform->setObjectName("contentWidget_transform");
        sizePolicy1.setHeightForWidth(contentWidget_transform->sizePolicy().hasHeightForWidth());
        contentWidget_transform->setSizePolicy(sizePolicy1);
        verticalLayout_6 = new QVBoxLayout(contentWidget_transform);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_position = new QLabel(contentWidget_transform);
        label_position->setObjectName("label_position");

        verticalLayout_6->addWidget(label_position);

        horizontalLayout_position = new QHBoxLayout();
        horizontalLayout_position->setObjectName("horizontalLayout_position");
        label_x_position = new QLabel(contentWidget_transform);
        label_x_position->setObjectName("label_x_position");

        horizontalLayout_position->addWidget(label_x_position);

        lineEditFloat_x_position = new LineEditFloat(contentWidget_transform);
        lineEditFloat_x_position->setObjectName("lineEditFloat_x_position");

        horizontalLayout_position->addWidget(lineEditFloat_x_position);

        label_y_position = new QLabel(contentWidget_transform);
        label_y_position->setObjectName("label_y_position");

        horizontalLayout_position->addWidget(label_y_position);

        lineEditFloat_y_position = new LineEditFloat(contentWidget_transform);
        lineEditFloat_y_position->setObjectName("lineEditFloat_y_position");

        horizontalLayout_position->addWidget(lineEditFloat_y_position);

        label_z_position = new QLabel(contentWidget_transform);
        label_z_position->setObjectName("label_z_position");

        horizontalLayout_position->addWidget(label_z_position);

        lineEditFloat_z_position = new LineEditFloat(contentWidget_transform);
        lineEditFloat_z_position->setObjectName("lineEditFloat_z_position");

        horizontalLayout_position->addWidget(lineEditFloat_z_position);


        verticalLayout_6->addLayout(horizontalLayout_position);

        line_2 = new QFrame(contentWidget_transform);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        label_scale = new QLabel(contentWidget_transform);
        label_scale->setObjectName("label_scale");

        verticalLayout_6->addWidget(label_scale);

        horizontalLayout_scale = new QHBoxLayout();
        horizontalLayout_scale->setObjectName("horizontalLayout_scale");
        label_x_scale = new QLabel(contentWidget_transform);
        label_x_scale->setObjectName("label_x_scale");

        horizontalLayout_scale->addWidget(label_x_scale);

        lineEditFloat_x_scale = new LineEditFloat(contentWidget_transform);
        lineEditFloat_x_scale->setObjectName("lineEditFloat_x_scale");

        horizontalLayout_scale->addWidget(lineEditFloat_x_scale);

        label_y_scale = new QLabel(contentWidget_transform);
        label_y_scale->setObjectName("label_y_scale");

        horizontalLayout_scale->addWidget(label_y_scale);

        lineEditFloat_y_scale = new LineEditFloat(contentWidget_transform);
        lineEditFloat_y_scale->setObjectName("lineEditFloat_y_scale");

        horizontalLayout_scale->addWidget(lineEditFloat_y_scale);

        label_z_scale = new QLabel(contentWidget_transform);
        label_z_scale->setObjectName("label_z_scale");

        horizontalLayout_scale->addWidget(label_z_scale);

        lineEditFloat_z_scale = new LineEditFloat(contentWidget_transform);
        lineEditFloat_z_scale->setObjectName("lineEditFloat_z_scale");

        horizontalLayout_scale->addWidget(lineEditFloat_z_scale);


        verticalLayout_6->addLayout(horizontalLayout_scale);

        line_3 = new QFrame(contentWidget_transform);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_3);

        label_2 = new QLabel(contentWidget_transform);
        label_2->setObjectName("label_2");

        verticalLayout_6->addWidget(label_2);

        horizontalLayout_rotation = new QHBoxLayout();
        horizontalLayout_rotation->setObjectName("horizontalLayout_rotation");
        label_x_rotation = new QLabel(contentWidget_transform);
        label_x_rotation->setObjectName("label_x_rotation");

        horizontalLayout_rotation->addWidget(label_x_rotation);

        lineEditFloat_x_rotation = new LineEditRotation(contentWidget_transform);
        lineEditFloat_x_rotation->setObjectName("lineEditFloat_x_rotation");

        horizontalLayout_rotation->addWidget(lineEditFloat_x_rotation);

        label_y_rotation = new QLabel(contentWidget_transform);
        label_y_rotation->setObjectName("label_y_rotation");

        horizontalLayout_rotation->addWidget(label_y_rotation);

        lineEditFloat_y_rotation = new LineEditRotation(contentWidget_transform);
        lineEditFloat_y_rotation->setObjectName("lineEditFloat_y_rotation");

        horizontalLayout_rotation->addWidget(lineEditFloat_y_rotation);

        label_z_rotation = new QLabel(contentWidget_transform);
        label_z_rotation->setObjectName("label_z_rotation");

        horizontalLayout_rotation->addWidget(label_z_rotation);

        lineEditFloat_z_rotation = new LineEditRotation(contentWidget_transform);
        lineEditFloat_z_rotation->setObjectName("lineEditFloat_z_rotation");

        horizontalLayout_rotation->addWidget(lineEditFloat_z_rotation);


        verticalLayout_6->addLayout(horizontalLayout_rotation);


        verticalLayout_3->addWidget(qCollapsibleWidget_transform);

        qCollapsibleWidget_color = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_color->setObjectName("qCollapsibleWidget_color");
        contentWidget_color = new QWidget(qCollapsibleWidget_color);
        contentWidget_color->setObjectName("contentWidget_color");
        sizePolicy1.setHeightForWidth(contentWidget_color->sizePolicy().hasHeightForWidth());
        contentWidget_color->setSizePolicy(sizePolicy1);
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

        qCollapsibleWidget_texture = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_texture->setObjectName("qCollapsibleWidget_texture");
        contentWidget_texture = new QWidget(qCollapsibleWidget_texture);
        contentWidget_texture->setObjectName("contentWidget_texture");
        sizePolicy1.setHeightForWidth(contentWidget_texture->sizePolicy().hasHeightForWidth());
        contentWidget_texture->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(contentWidget_texture);
        horizontalLayout->setObjectName("horizontalLayout");
        label_textureViewer = new QLabel(contentWidget_texture);
        label_textureViewer->setObjectName("label_textureViewer");
        sizePolicy3.setHeightForWidth(label_textureViewer->sizePolicy().hasHeightForWidth());
        label_textureViewer->setSizePolicy(sizePolicy3);
        label_textureViewer->setMinimumSize(QSize(64, 64));

        horizontalLayout->addWidget(label_textureViewer);

        comboBox_texture = new AdvancedComboBox(contentWidget_texture);
        comboBox_texture->setObjectName("comboBox_texture");

        horizontalLayout->addWidget(comboBox_texture);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(qCollapsibleWidget_texture);

        qCollapsibleWidget_camera = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_camera->setObjectName("qCollapsibleWidget_camera");
        contentWidget_camera = new QWidget(qCollapsibleWidget_camera);
        contentWidget_camera->setObjectName("contentWidget_camera");
        sizePolicy1.setHeightForWidth(contentWidget_camera->sizePolicy().hasHeightForWidth());
        contentWidget_camera->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(contentWidget_camera);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_isPrimary = new QLabel(contentWidget_camera);
        label_isPrimary->setObjectName("label_isPrimary");

        horizontalLayout_2->addWidget(label_isPrimary);

        checkBox_isPrimary = new QCheckBox(contentWidget_camera);
        checkBox_isPrimary->setObjectName("checkBox_isPrimary");

        horizontalLayout_2->addWidget(checkBox_isPrimary);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_3->addWidget(qCollapsibleWidget_camera);

        qCollapsibleWidget_script = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_script->setObjectName("qCollapsibleWidget_script");
        contentWidget_script = new QWidget(qCollapsibleWidget_script);
        contentWidget_script->setObjectName("contentWidget_script");
        sizePolicy1.setHeightForWidth(contentWidget_script->sizePolicy().hasHeightForWidth());
        contentWidget_script->setSizePolicy(sizePolicy1);
        horizontalLayout_8 = new QHBoxLayout(contentWidget_script);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_script = new QLabel(contentWidget_script);
        label_script->setObjectName("label_script");

        horizontalLayout_8->addWidget(label_script);

        comboBox_script = new AdvancedComboBox(contentWidget_script);
        comboBox_script->setObjectName("comboBox_script");

        horizontalLayout_8->addWidget(comboBox_script);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_3->addWidget(qCollapsibleWidget_script);

        qCollapsibleWidget_rigidbody2D = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_rigidbody2D->setObjectName("qCollapsibleWidget_rigidbody2D");
        contentWidget_rigidbody2D = new QWidget(qCollapsibleWidget_rigidbody2D);
        contentWidget_rigidbody2D->setObjectName("contentWidget_rigidbody2D");
        sizePolicy1.setHeightForWidth(contentWidget_rigidbody2D->sizePolicy().hasHeightForWidth());
        contentWidget_rigidbody2D->setSizePolicy(sizePolicy1);
        verticalLayout_10 = new QVBoxLayout(contentWidget_rigidbody2D);
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_bodyType = new QLabel(contentWidget_rigidbody2D);
        label_bodyType->setObjectName("label_bodyType");

        horizontalLayout_6->addWidget(label_bodyType);

        comboBox_bodyType = new QComboBox(contentWidget_rigidbody2D);
        comboBox_bodyType->addItem(QString());
        comboBox_bodyType->addItem(QString());
        comboBox_bodyType->addItem(QString());
        comboBox_bodyType->setObjectName("comboBox_bodyType");

        horizontalLayout_6->addWidget(comboBox_bodyType);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_10->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_fixedRotation = new QLabel(contentWidget_rigidbody2D);
        label_fixedRotation->setObjectName("label_fixedRotation");

        horizontalLayout_7->addWidget(label_fixedRotation);

        checkBox_fixedRotation = new QCheckBox(contentWidget_rigidbody2D);
        checkBox_fixedRotation->setObjectName("checkBox_fixedRotation");

        horizontalLayout_7->addWidget(checkBox_fixedRotation);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_10->addLayout(horizontalLayout_7);


        verticalLayout_3->addWidget(qCollapsibleWidget_rigidbody2D);

        qCollapsibleWidget_boxCollider2D = new QCollapsibleWidget(scrollAreaWidgetContents_detail);
        qCollapsibleWidget_boxCollider2D->setObjectName("qCollapsibleWidget_boxCollider2D");
        contentWidget_boxCollider2D = new QWidget(qCollapsibleWidget_boxCollider2D);
        contentWidget_boxCollider2D->setObjectName("contentWidget_boxCollider2D");
        sizePolicy1.setHeightForWidth(contentWidget_boxCollider2D->sizePolicy().hasHeightForWidth());
        contentWidget_boxCollider2D->setSizePolicy(sizePolicy1);
        verticalLayout_11 = new QVBoxLayout(contentWidget_boxCollider2D);
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_boxCollider2D_offset = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_offset->setObjectName("label_boxCollider2D_offset");

        verticalLayout_11->addWidget(label_boxCollider2D_offset);

        horizontalLayout_boxCollider2D_offset = new QHBoxLayout();
        horizontalLayout_boxCollider2D_offset->setObjectName("horizontalLayout_boxCollider2D_offset");
        label_boxCollider2D_offset_x = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_offset_x->setObjectName("label_boxCollider2D_offset_x");

        horizontalLayout_boxCollider2D_offset->addWidget(label_boxCollider2D_offset_x);

        lineEditFloat_boxCollider2D_offset_x = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_offset_x->setObjectName("lineEditFloat_boxCollider2D_offset_x");

        horizontalLayout_boxCollider2D_offset->addWidget(lineEditFloat_boxCollider2D_offset_x);

        label_boxCollider2D_offset_y = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_offset_y->setObjectName("label_boxCollider2D_offset_y");

        horizontalLayout_boxCollider2D_offset->addWidget(label_boxCollider2D_offset_y);

        lineEditFloat_boxCollider2D_offset_y = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_offset_y->setObjectName("lineEditFloat_boxCollider2D_offset_y");

        horizontalLayout_boxCollider2D_offset->addWidget(lineEditFloat_boxCollider2D_offset_y);


        verticalLayout_11->addLayout(horizontalLayout_boxCollider2D_offset);

        label_boxCollider2D_size = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_size->setObjectName("label_boxCollider2D_size");

        verticalLayout_11->addWidget(label_boxCollider2D_size);

        horizontalLayout_boxCollider2D_size = new QHBoxLayout();
        horizontalLayout_boxCollider2D_size->setObjectName("horizontalLayout_boxCollider2D_size");
        label_boxCollider2D_size_x = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_size_x->setObjectName("label_boxCollider2D_size_x");

        horizontalLayout_boxCollider2D_size->addWidget(label_boxCollider2D_size_x);

        lineEditFloat_boxCollider2D_size_x = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_size_x->setObjectName("lineEditFloat_boxCollider2D_size_x");

        horizontalLayout_boxCollider2D_size->addWidget(lineEditFloat_boxCollider2D_size_x);

        label_boxCollider2D_size_y = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_size_y->setObjectName("label_boxCollider2D_size_y");

        horizontalLayout_boxCollider2D_size->addWidget(label_boxCollider2D_size_y);

        lineEditFloat_boxCollider2D_size_y = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_size_y->setObjectName("lineEditFloat_boxCollider2D_size_y");

        horizontalLayout_boxCollider2D_size->addWidget(lineEditFloat_boxCollider2D_size_y);


        verticalLayout_11->addLayout(horizontalLayout_boxCollider2D_size);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_boxCollider2D_density = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_density->setObjectName("label_boxCollider2D_density");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_boxCollider2D_density);

        lineEditFloat_boxCollider2D_density = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_density->setObjectName("lineEditFloat_boxCollider2D_density");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditFloat_boxCollider2D_density);

        label_boxCollider2D_friction = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_friction->setObjectName("label_boxCollider2D_friction");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_boxCollider2D_friction);

        lineEditFloat_boxCollider2D_friction = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_friction->setObjectName("lineEditFloat_boxCollider2D_friction");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditFloat_boxCollider2D_friction);

        label_boxCollider2D_restitution = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_restitution->setObjectName("label_boxCollider2D_restitution");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_boxCollider2D_restitution);

        label_boxCollider2D_restitutionThreshold = new QLabel(contentWidget_boxCollider2D);
        label_boxCollider2D_restitutionThreshold->setObjectName("label_boxCollider2D_restitutionThreshold");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_boxCollider2D_restitutionThreshold);

        lineEditFloat_boxCollider2D_restitution = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_restitution->setObjectName("lineEditFloat_boxCollider2D_restitution");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditFloat_boxCollider2D_restitution);

        lineEditFloat_boxCollider2D_restitutionThreshold = new LineEditFloat(contentWidget_boxCollider2D);
        lineEditFloat_boxCollider2D_restitutionThreshold->setObjectName("lineEditFloat_boxCollider2D_restitutionThreshold");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditFloat_boxCollider2D_restitutionThreshold);


        verticalLayout_11->addLayout(formLayout);


        verticalLayout_3->addWidget(qCollapsibleWidget_boxCollider2D);

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
        treeWidget = new OutlineTreeWidget(wrapWidgetRight);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 812, 229));
        gridLayout_6 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setVerticalSpacing(0);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        contentBrowserPanel = new ContentBrowserPanel(scrollAreaWidgetContents);
        contentBrowserPanel->setObjectName("contentBrowserPanel");

        gridLayout_6->addWidget(contentBrowserPanel, 0, 0, 1, 1);

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
        titlebar = new Titlebar(MainWindow);
        titlebar->setObjectName("titlebar");
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(titlebar->sizePolicy().hasHeightForWidth());
        titlebar->setSizePolicy(sizePolicy4);
        titlebar->setFeatures(QDockWidget::NoDockWidgetFeatures);
        titlebarContents = new QWidget();
        titlebarContents->setObjectName("titlebarContents");
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(titlebarContents->sizePolicy().hasHeightForWidth());
        titlebarContents->setSizePolicy(sizePolicy5);
        verticalLayout_8 = new QVBoxLayout(titlebarContents);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(6, 3, 3, 3);
        titlebarLayout = new QHBoxLayout();
        titlebarLayout->setObjectName("titlebarLayout");
        titlebarLayout->setContentsMargins(0, 2, -1, -1);
        label_windowIcon = new QLabel(titlebarContents);
        label_windowIcon->setObjectName("label_windowIcon");
        label_windowIcon->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_windowIcon->sizePolicy().hasHeightForWidth());
        label_windowIcon->setSizePolicy(sizePolicy3);
        label_windowIcon->setMinimumSize(QSize(0, 0));
        label_windowIcon->setBaseSize(QSize(0, 0));
        label_windowIcon->setPixmap(QPixmap(QString::fromUtf8(":/icon/icon/windowIcon.jpg")));

        titlebarLayout->addWidget(label_windowIcon);

        label_windowTitle = new QLabel(titlebarContents);
        label_windowTitle->setObjectName("label_windowTitle");

        titlebarLayout->addWidget(label_windowTitle);

        menubarLayout = new QHBoxLayout();
        menubarLayout->setObjectName("menubarLayout");
        menubarLayout->setContentsMargins(-1, 0, -1, -1);

        titlebarLayout->addLayout(menubarLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        titlebarLayout->addItem(horizontalSpacer_3);

        pushButton_minimize = new QPushButton(titlebarContents);
        pushButton_minimize->setObjectName("pushButton_minimize");
        sizePolicy3.setHeightForWidth(pushButton_minimize->sizePolicy().hasHeightForWidth());
        pushButton_minimize->setSizePolicy(sizePolicy3);
        pushButton_minimize->setMinimumSize(QSize(32, 32));
        pushButton_minimize->setMaximumSize(QSize(32, 32));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/minimize.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_minimize->setIcon(icon);

        titlebarLayout->addWidget(pushButton_minimize);

        pushButton_expand = new QPushButton(titlebarContents);
        pushButton_expand->setObjectName("pushButton_expand");
        pushButton_expand->setMinimumSize(QSize(32, 32));
        pushButton_expand->setMaximumSize(QSize(32, 32));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/expand-window-max.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/icon/icon/expand-window-min.png"), QSize(), QIcon::Selected, QIcon::On);
        pushButton_expand->setIcon(icon1);

        titlebarLayout->addWidget(pushButton_expand);

        pushButton_close = new QPushButton(titlebarContents);
        pushButton_close->setObjectName("pushButton_close");
        pushButton_close->setMinimumSize(QSize(32, 32));
        pushButton_close->setMaximumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_close->setIcon(icon2);

        titlebarLayout->addWidget(pushButton_close);


        verticalLayout_8->addLayout(titlebarLayout);

        titlebar->setWidget(titlebarContents);
        MainWindow->addDockWidget(Qt::TopDockWidgetArea, titlebar);

        retranslateUi(MainWindow);

        tabWidget_manager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Engine Editor", nullptr));
        dockWidgetLeft->setWindowTitle(QCoreApplication::translate("MainWindow", "Object information", nullptr));
        qCollapsibleWidget_tag->setTitle(QCoreApplication::translate("MainWindow", "Tag", nullptr));
        label_tag->setText(QCoreApplication::translate("MainWindow", "Tag", nullptr));
        qCollapsibleWidget_transform->setTitle(QCoreApplication::translate("MainWindow", "Transform", nullptr));
        label_position->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        label_x_position->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_y_position->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_z_position->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_scale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        label_x_scale->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_y_scale->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_z_scale->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Rotation", nullptr));
        label_x_rotation->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_y_rotation->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_z_rotation->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        qCollapsibleWidget_color->setTitle(QCoreApplication::translate("MainWindow", "Color", nullptr));
        label_R_color->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_G_color->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        label_B_color->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "color", nullptr));
        pushButton_colorPicker->setText(QCoreApplication::translate("MainWindow", "choose color", nullptr));
        qCollapsibleWidget_texture->setTitle(QCoreApplication::translate("MainWindow", "Texture", nullptr));
        label_textureViewer->setText(QString());
        qCollapsibleWidget_camera->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        label_isPrimary->setText(QCoreApplication::translate("MainWindow", "Is primary", nullptr));
        checkBox_isPrimary->setText(QString());
        qCollapsibleWidget_script->setTitle(QCoreApplication::translate("MainWindow", "Script", nullptr));
        label_script->setText(QCoreApplication::translate("MainWindow", "Class", nullptr));
        qCollapsibleWidget_rigidbody2D->setTitle(QCoreApplication::translate("MainWindow", "Rigidbody2D", nullptr));
        qCollapsibleWidget_rigidbody2D->setPushButtonStyle(QString());
        label_bodyType->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboBox_bodyType->setItemText(0, QCoreApplication::translate("MainWindow", "Static", nullptr));
        comboBox_bodyType->setItemText(1, QCoreApplication::translate("MainWindow", "Dynamic", nullptr));
        comboBox_bodyType->setItemText(2, QCoreApplication::translate("MainWindow", "Kinematic", nullptr));

        label_fixedRotation->setText(QCoreApplication::translate("MainWindow", "Fix rotation", nullptr));
        checkBox_fixedRotation->setText(QString());
        qCollapsibleWidget_boxCollider2D->setTitle(QCoreApplication::translate("MainWindow", "BoxCollider2D", nullptr));
        label_boxCollider2D_offset->setText(QCoreApplication::translate("MainWindow", "Offset", nullptr));
        label_boxCollider2D_offset_x->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_boxCollider2D_offset_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_boxCollider2D_size->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        label_boxCollider2D_size_x->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_boxCollider2D_size_y->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_boxCollider2D_density->setText(QCoreApplication::translate("MainWindow", "Density", nullptr));
        label_boxCollider2D_friction->setText(QCoreApplication::translate("MainWindow", "Friction", nullptr));
        label_boxCollider2D_restitution->setText(QCoreApplication::translate("MainWindow", "Restitution", nullptr));
        label_boxCollider2D_restitutionThreshold->setText(QCoreApplication::translate("MainWindow", "Restitution threshold", nullptr));
        dockWidgetRight->setWindowTitle(QCoreApplication::translate("MainWindow", "Game Objects", nullptr));
        dockWidgetBottom->setWindowTitle(QCoreApplication::translate("MainWindow", "Manager", nullptr));
        tabWidget_manager->setTabText(tabWidget_manager->indexOf(tab_assets), QCoreApplication::translate("MainWindow", "Assets", nullptr));
        tabWidget_manager->setTabText(tabWidget_manager->indexOf(tab_console), QCoreApplication::translate("MainWindow", "Console", nullptr));
        label_windowIcon->setText(QString());
        label_windowTitle->setText(QCoreApplication::translate("MainWindow", "GameEngine", nullptr));
        pushButton_minimize->setText(QString());
        pushButton_expand->setText(QString());
        pushButton_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
