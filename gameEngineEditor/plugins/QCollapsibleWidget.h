#ifndef QCOLLAPSIBLEWIDGET_H
#define QCOLLAPSIBLEWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QChildEvent>
#include <QList>

class QCollapsibleWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString Title READ getTitle WRITE setTitle)
    Q_PROPERTY(QString PushButtonStyle READ getPushButtonStyle WRITE setPushButtonStyle);
public:
    QCollapsibleWidget(QWidget *parent = 0);

    QString getTitle() const;
    void setTitle(QString title);
    void setLayout(QLayout* layout);
    QString getPushButtonStyle() const;
    void setPushButtonStyle(QString styleSheet);
    inline QWidget* getContentWidget()
    {
        return this->contentWidget;
    }
public slots:
    void changeContentState();
protected:
    void childEvent(QChildEvent *event) override;
private:
    QVBoxLayout* verticalLayout;
    QPushButton* pushButton;
    QWidget* contentWidget;
    bool isContentClose;
    //if true，代表是由c++加入，不是Designer
    bool needToInsertPushButton;
};

#endif // QCOLLAPSIBLEWIDGET_H
