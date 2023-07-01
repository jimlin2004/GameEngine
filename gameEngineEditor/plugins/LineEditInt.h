#ifndef LINEEDITINT_H
#define LINEEDITINT_H

#include <QLineEdit>
#include <exception>

class LineEditInt : public QLineEdit
{
    Q_OBJECT

public:
    LineEditInt(QWidget *parent = 0);
    void bind(int* ptr);
    int getValue() const;
    void setValue(int val);
private:
    int* _dataPtr;
private slots:
    void onEditingFinished();
};

#endif // LINEEDITINT_H
