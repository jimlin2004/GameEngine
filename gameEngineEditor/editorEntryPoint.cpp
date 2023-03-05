#include "mainwindow.h"

#include <QDebug>
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 0);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow w;
    w.show();

    qDebug("Create Editor success\n");
    qDebug("Running environment version: %s\n", "1.0 alpha");

    return a.exec();
}