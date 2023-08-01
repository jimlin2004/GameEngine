#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QDockWidget>
#include <QMouseEvent>

class Titlebar: public QDockWidget
{
    Q_OBJECT
public:
    explicit Titlebar(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
signals:
    void onMousePressEventSignal(void);
    void onMouseDoubleClickEventSignal(void);
    void onHitBorderSignal(QPoint);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif