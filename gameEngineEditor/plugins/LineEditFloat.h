#ifndef LINEEDITFLOAT_H
#define LINEEDITFLOAT_H

#include <QLineEdit>
#include <exception>

class LineEditFloat : public QLineEdit
{
    Q_OBJECT

public:
    LineEditFloat(QWidget *parent = 0);
    void bind(float* ptr);
    float getValue() const;
    void setValue(float val);
private:
    float* _dataPtr;
private slots:
    void onEditingFinished();
};

#endif // LINEEDITFLOAT_H
