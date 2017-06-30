#ifndef SHOWMOREH
#define SHOWMOREH

#include <QWidget>
#include "classwidget.h"
#include "classtop.h"

class ShowMore : public QWidget
{
    Q_OBJECT
public:
    explicit ShowMore(QWidget *parent = 0);
    QWidget *moreWidget;
    void setElementName(int category);
    void setTopName(int category);
private:
    ClassTop *moreClassTop;
    QVBoxLayout *mainLayout;
    Element *moreElement;
    QGridLayout *eleLayout;
    bool eventFilter(QObject *watched, QEvent *event);
    QWidget  *spaceWidget;
    int categoryFlag;
};

#endif // SHOWMOREH
