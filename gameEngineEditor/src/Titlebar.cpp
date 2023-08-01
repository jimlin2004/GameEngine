#include "Titlebar.h"

Titlebar::Titlebar(QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags)
{
    this->setTitleBarWidget(new QWidget());
}

void Titlebar::mousePressEvent(QMouseEvent *event)
{
    static constexpr int border = 6;
    if (event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        if (pos.x() < border || pos.x() > this->width() - border || pos.y() < border)
        {
            emit this->onHitBorderSignal(pos);
            return;
        }
        emit this->onMousePressEventSignal();
    }
    return QDockWidget::mousePressEvent(event);
}

void Titlebar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit this->onMouseDoubleClickEventSignal();
    return QDockWidget::mouseDoubleClickEvent(event);
}