#include "LineEditInt.h"

LineEditInt::LineEditInt(QWidget *parent)
    : QLineEdit(parent)
    , _dataPtr(nullptr)
    , _isEditing(false)
{
    connect(this, &LineEditInt::editingFinished, this, &LineEditInt::onEditingFinished);
    this->setEnabled(false);
}

void LineEditInt::bind(int* ptr)
{
    if (ptr == nullptr)
        return;
    this->_dataPtr = ptr;
    this->setEnabled(true);
    this->setText(QString::number(*(ptr)));
}

void LineEditInt::onEditingFinished()
{
    if (this->_dataPtr == nullptr)
        return;
    this->setValue(this->text().toInt());
}

int LineEditInt::getValue() const
{
    if (this->_dataPtr == nullptr)
        throw std::runtime_error("must bind data pointer before get its value");
    return *(this->_dataPtr);
}

void LineEditInt::setValue(int val)
{
    if (this->_dataPtr == nullptr)
        throw std::runtime_error("must bind data pointer before set its value");
    (*this->_dataPtr) = val;
    this->setText(QString::number(*(this->_dataPtr)));
}

void LineEditInt::refresh()
{
    if (this->_dataPtr != nullptr)
        this->setText(QString::number(*(this->_dataPtr)));
}

void LineEditInt::focusInEvent(QFocusEvent* event)
{
    this->_isEditing = true;
    QLineEdit::focusInEvent(event);
}

void LineEditInt::focusOutEvent(QFocusEvent* event)
{
    this->_isEditing = false;
    QLineEdit::focusOutEvent(event);
}
