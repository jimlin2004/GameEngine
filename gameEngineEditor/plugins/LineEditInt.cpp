#include "LineEditInt.h"

LineEditInt::LineEditInt(QWidget *parent)
    : QLineEdit(parent)
    , _dataPtr(nullptr)
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
    (*this->_dataPtr) = this->text().toInt();
}

int LineEditInt::getValue() const
{
    if (this->_dataPtr == nullptr)
        throw std::runtime_error("must bind data pointer before get its value");
    return this->text().toInt();
}
