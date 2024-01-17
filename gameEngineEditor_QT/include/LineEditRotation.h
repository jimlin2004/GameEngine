#ifndef LINE_EDIT_ROTATION
#define LINE_EDIT_ROTATION

#include "LineEditFloat.h"

class LineEditRotation: public LineEditFloat
{
    Q_OBJECT
public:
    LineEditRotation(QWidget *parent = 0);
    virtual void setValue(float val) override;
private slots:
    virtual void onEditingFinished() override;
};

#endif