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
    virtual void setValue(int val);
    void refresh();
    inline bool isEditing() const
    {
        return this->_isEditing;
    }
private slots:
    virtual void onEditingFinished();
protected:
    int* _dataPtr;
    bool _isEditing;
    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;
};

#endif // LINEEDITINT_H
