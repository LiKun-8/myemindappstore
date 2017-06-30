#ifndef ELEMENTH
#define ELEMENTH
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "custombutton.h"

class Element:public QObject
{
    Q_OBJECT

public:
    Element();
    ~Element();

    QWidget *baseWidget;
    void init();//初始化布局
    void setBtnImage(const QString& imagePath);//设置应用图标
    void setBtnName(const QString& name);//设置应用名字
    void setBtnStart();//设置应用评分
    void setBtnStatus(const QString& status);//设置应用状态
    void setButton(bool);
    int category;//应用的分类
    void setcategory(const int& cate);//设置应用分类

private slots:
    void btnStatusSlot();

private:
    QPushButton *btnImage;
    QPushButton *btnName;
    QPushButton *btnstar;
    CustomButton *btnStatus;//自定义的按钮
    QVBoxLayout *vbLayout;
    QHBoxLayout *hbLayout;
};

#endif // ELEMENTH

