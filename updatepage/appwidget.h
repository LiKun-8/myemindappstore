#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>

class AppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppWidget(QWidget *parent ,QString headUrl,QString nameStr,QString sizeStr,QString verStr,QString logStr);
    bool event(QEvent *event);
    void getImage(QString headUrl);
signals:
    void sigIntroResize();

private slots:
    void getImageFinished(QNetworkReply *reply);

public:
    QHBoxLayout *appLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *bottomLayout;
    QPushButton *headButton;
    QPushButton *nameButton;
    QLabel *introLabel;
    QString introstr;
    QPushButton *funcButton;
    QLabel *sizeLabel;
    QLabel *versionLabel;
    QPushButton *updateButton;
    QPixmap pix;
    QString changeLog;
    QNetworkAccessManager *imageUpdate;

};

#endif // APPWIDGET_H
