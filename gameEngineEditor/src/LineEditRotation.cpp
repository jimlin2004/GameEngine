#include "LineEditRotation.h"

#include "glm/glm.hpp"

LineEditRotation::LineEditRotation(QWidget *parent)
    : LineEditFloat(parent)
{
}

void LineEditRotation::setValue(float val)
{
    LineEditFloat::setValue(glm::radians(val));
}

void LineEditRotation::onEditingFinished()
{
    if (this->_dataPtr == nullptr)
        return;
    *(this->_dataPtr) = glm::radians(this->text().toFloat());

}