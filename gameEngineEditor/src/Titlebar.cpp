#include "Titlebar.h"

Titlebar::Titlebar(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags)
{
    this->setTitleBarWidget(new QWidget());
}

void onMousePressEventSignal(void)
{
}

void Titlebar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit this->onMousePressEventSignal();
    return QWidget::mousePressEvent(event);
}
