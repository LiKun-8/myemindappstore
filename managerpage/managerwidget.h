#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class ManagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManagerWidget(QWidget *parent ,QString namestr, QString verstr, QString sizestr);
    void setManagerButton(QString manastr);
    QPushButton * GetButton(int num);

private:
    QHBoxLayout *hbLayout;
    QVBoxLayout *vbLayout;
    QPushButton *headButton;
    QPushButton *nameButton;
    QLabel *verLabel;
    QLabel *sizeLabel;
    QPushButton *uninsButton;
    QPushButton *managerButton;


signals:

public slots:
};

#endif // MANAGERWIDGET_H
