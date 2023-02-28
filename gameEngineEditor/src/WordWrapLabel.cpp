#include "WordWrapLabel.h"

WordWrapLabel::WordWrapLabel(QWidget *parent)
    : QLabel(parent)
{

}

WordWrapLabel::WordWrapLabel(const QString& text, QWidget *parent)
    : QLabel(text, parent)
{
    
}

WordWrapLabel::~WordWrapLabel()
{

}

QString splitText(const QFontMetrics& fm, const QString& text, int labelWidth)
{
    int textSize = fm.size(0, text).width();
    if (textSize > labelWidth)
    {
        int pos = 0;
        int offset = 0;
        for (int i = 0; i < text.size(); ++i)
        {
            offset += fm.size(0, text[i]).width();
            if (offset > labelWidth)
            {
                pos = i;
                break;
            }
        }
        QString leftText = text.left(pos);
        QString midText = text.mid(pos);
        return leftText + "\n" + splitText(fm, midText, labelWidth);
    }
    return text;
}

void WordWrapLabel::wrapText(const QString& text)
{
    QFontMetrics fm(this->font());
    int textWidth = fm.size(0, text).width();
    int labelWidth = this->width();
    if (textWidth > labelWidth)
    {
        if (!text.isEmpty())
        {
            int charWidth = fm.size(0, text[0]).width();
            if (charWidth > labelWidth)
            {
                this->setMinimumWidth(charWidth); //至少1字符寬度
            }
        }
        labelWidth = this->width();
        QString newText = splitText(fm, text, labelWidth);
        QLabel::setText(newText);
        return;
    }
    QLabel::setText(text);
}