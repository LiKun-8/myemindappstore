#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>

class ManagerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ManagerWidget(QWidget *parent ,QString urlstr,QString namestr, QString verstr, QString sizestr);
    void setManagerButton(QString manastr);
    QPushButton * GetButton(int num);
    void getImage(QString headUrl);


private:
    QHBoxLayout *hbLayout;
    QVBoxLayout *vbLayout;
    QPushButton *headButton;
    QPushButton *nameButton;
    QLabel *verLabel;
    QLabel *sizeLabel;
    QPushButton *uninsButton;
    QPushButton *managerButton;
    QNetworkAccessManager *imageManager;

signals:

public slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // MANAGERWIDGET_H
