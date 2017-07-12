#ifndef UPDATEPAGE_H
#define UPDATEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QPointer>
#include <packagekitqt5/PackageKit/Daemon>
#include <packagekitqt5/PackageKit/Transaction>
#include "taskbar.h"
#include "appwidget.h"
#include "funcwidget.h"

class UpdatePage : public QWidget
{
    Q_OBJECT
public:
    explicit UpdatePage(QWidget *parent = 0);
    void CreateUpdateWindow();
    void getUpdates();

    int count() const;

private:
    QWidget *pageUpdateWidget;
    TaskBar *updTaskBar;
    QTableWidget *updateTable;
    QVBoxLayout *upVLayout;
    QScrollArea *upScroArea;
    bool event(QEvent *event);


signals:
    void done();

public slots:
    void PageUpdateBtnClicked();
    void StrLenChanged();
    void TextAreaChanged(int hig);

};

#endif // UPDATEPAGE_H
