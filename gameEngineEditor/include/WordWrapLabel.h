#ifndef WORD_WRAP_LABEL_H
#define WORD_WRAP_LABEL_H

#include <QLabel>

class WordWrapLabel: public QLabel
{
    Q_OBJECT

public:
    WordWrapLabel(QWidget *parent = nullptr);
    WordWrapLabel(const QString& text, QWidget *parent = nullptr);
// private:
    void wrapText(const QString& text);
};

#endif