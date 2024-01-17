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
    virtual void setValue(float val);
    void refresh();
    inline bool isEditing() const
    {
        return this->_isEditing;
    }
private slots:
    virtual void onEditingFinished();
protected:
    float* _dataPtr;
    bool _isEditing;
    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;
};

#endif // LINEEDITFLOAT_H
