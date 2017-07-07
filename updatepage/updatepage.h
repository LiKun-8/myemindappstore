#ifndef UPDATEPAGE_H
#define UPDATEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>
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

private:
    QWidget *pageUpdateWidget;
    TaskBar *updTaskBar;
    QTableWidget *updateTable;
    QVBoxLayout *upVLayout;
    QScrollArea *upScroArea;
    bool event(QEvent *event);
signals:

public slots:
    void PageUpdateBtnClicked();
    void StrLenChanged();
    void TextAreaChanged(int hig);
};

#endif // UPDATEPAGE_H
