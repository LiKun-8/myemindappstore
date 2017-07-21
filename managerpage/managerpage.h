#ifndef MANAGERPAGE_H
#define MANAGERPAGE_H

#include <QWidget>
#include <QEvent>
#include "updatepage/taskbar.h"
#include "managerpage/managerwidget.h"
#include "../updatepage/pkupdates.h"

class ManagerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ManagerPage(QWidget *parent = 0);
    void CreateManagerWindow();
    bool event(QEvent *event);

private:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QVBoxLayout *vboxLayout2;
    TaskBar *manTaskBar;
    TaskBar *manCompBar;
    QTableWidget *installTable;
    QTableWidget *compTable;
    QLabel *splitLabel;
    ManagerWidget *compManager;
    QScrollArea *manScroArea;
    PkUpdates *updm;

signals:

public slots:
    void onGetInsFinished(QVariantMap insdMap);
};

#endif // MANAGERPAGE_H
