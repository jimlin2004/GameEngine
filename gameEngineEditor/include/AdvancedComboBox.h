#ifndef ADVANCED_COMBOBOX_H
#define ADVANCED_COMBOBOX_H

#include <QComboBox>

#include <QWheelEvent>

class AdvancedComboBox: public QComboBox
{
    Q_OBJECT
public:
    explicit AdvancedComboBox(QWidget* parent = nullptr);

    //是否啟用滑鼠滾輪事件
    void enableWheelEvent(bool enable = true);

    void wheelEvent(QWheelEvent *event);
private:
    bool isEnabledWheelEvent;
};

#endif