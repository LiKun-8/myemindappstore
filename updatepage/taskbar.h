#ifndef TASKBAR_H
#define TASKBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class TaskBar : public QWidget
{
    Q_OBJECT
public:
    explicit TaskBar(QWidget *parent,QString taskstr,QString onekeystr);
    void hideOnekeyButton();
private:
    QHBoxLayout *hbLayout;
    QLabel *vblueLabel;
    QLabel *taskLabel;
    QPushButton *onekeyButton;
    QString taskStr;
    QString onekeyStr;


signals:

public slots:
};

#endif // TASKBAR_H
