#ifndef CLASSWIDGETH
#define CLASSWIDGETH
#include <QMainWindow>
#include "element.h"
#include "classtop.h"
#include <QLabel>
#define MARGIN 32;
#define SPACING 192;
#include <QWidget>
#include <QLayoutItem>


class ClassWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassWidget(QWidget *parent = 0);
    ~ClassWidget();
    QWidget *widget;
    void setCategory(const int& cate);//设置分类标志
    void setTopName();//设置分类项的名字
    void setElementName();//设置软件的名字
    void initElement();//初始化软件对象

private:
    //每一个软件项`
    Element *tt;
    //每个分类项的顶部
    ClassTop *classtop;
    //软件项布局
    QGridLayout *gridLayout;
    //软件项的列表
    QVector<QWidget *> demoElement;
    //主布局
    QVBoxLayout *mainLayout;
    //弹簧布局
    QSpacerItem *spacer;
    //分类的标志
    int category;
    //空白widget
    QWidget *spaceWidget;

    int index;
    QLayoutItem *child;
protected:
    //重写的窗口变化事件
    bool eventFilter(QObject *target, QEvent *event);

signals:
    void moreShow(int);

protected slots:
    void sendMoreShow(int i);
};

#endif // CLASSWIDGETH
