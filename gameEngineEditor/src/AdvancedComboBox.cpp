#include "AdvancedComboBox.h"

AdvancedComboBox::AdvancedComboBox(QWidget *parent)
    : QComboBox(parent)
    , isEnabledWheelEvent(false)
{
}

void AdvancedComboBox::enableWheelEvent(bool enable)
{
    this->isEnabledWheelEvent = enable;
}

void AdvancedComboBox::wheelEvent(QWheelEvent *event)
{
    if (this->isEnabledWheelEvent)
        QComboBox::wheelEvent(event);
}
