#include "showmore.h"
#include <QDebug>
//#include "jsonfunc.h"
#define MAXNUMBER 180

extern QMap<int,QString> cateMap;
//extern QMap<int,SORTSTRUCT>  sortStrMap;
extern QMap<int,int> sortElementNum;

ShowMore::ShowMore(QWidget *parent) : QWidget(parent)
{
    moreWidget = new QWidget();
    moreClassTop = new ClassTop();
    moreClassTop->setTopbtnHide();
    mainLayout = new QVBoxLayout();
    moreElement = new Element[MAXNUMBER];
    eleLayout = new QGridLayout();
    eleLayout->setSpacing(24);
    moreWidget->setMinimumSize(640,0);
    moreWidget->installEventFilter(this);
    eleLayout->setContentsMargins(16,0,16,0);

    int test = 0;
    for(int i = 0;i<36;i++)
    {
        for(int j = 0;j<5;j++)
        {
            eleLayout->addWidget(moreElement[test].baseWidget,i,j,1,1,Qt::AlignLeft);
            moreElement[test].baseWidget->hide();

            if(test < (MAXNUMBER-1))
            {
                test++;
            }
            else
            {
                break;
            }
        }
    }

    categoryFlag = -1;
    spaceWidget = new QWidget[5];
    mainLayout->addWidget(moreClassTop->widget);
    mainLayout->addLayout(eleLayout);
    moreWidget->setLayout(mainLayout);
}

//设置软件名字
void ShowMore::setElementName(int category)
{
//    if(sortStrMap.isEmpty())
//    {
//        qDebug()<<"the sortstr is empty!"<<endl;
//    }

//    QMap<int,SORTSTRUCT>::iterator item = sortStrMap.begin();

//    int showNum = 0;
//    for(;item != sortStrMap.end();++item)
//    {
//        if(item.value().category == (category+1))
//        {
//            moreElement[showNum].setBtnName(item.value().btnname);
//            moreElement[showNum].baseWidget->show();
//            showNum++;
//        }
//    }

//    for(int hideNum = showNum;hideNum<MAXNUMBER;hideNum++)
//    {
//        moreElement[hideNum].baseWidget->hide();

//    }
}

//设置软件类名字
void ShowMore::setTopName(int category)
{
//    categoryFlag = category;
//    if(cateMap.isEmpty())
//    {
//        qDebug()<<"the cateMap is empty!"<<endl;
//    }

//    if(cateMap.contains(category+1))
//    {
//        QMap<int,QString>::iterator it = cateMap.find(category+1);
//        moreClassTop->setLabelData(it.value());
//    }
}

bool ShowMore::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == moreWidget)
    {
        if(event->type() == QEvent::Resize)
        {
            if(categoryFlag == -1)
            {
                return true;
            }

//            QMap<int,int>::iterator it = sortElementNum.find(categoryFlag+1);
//            int numElement = it.value();
            int numElement = 15;
            int column = (moreWidget->size().width()+48)/192;
            int row;

            if(numElement%column == 0)
            {
                row  = (numElement/column);
            }
            else
            {
                row  = (numElement/column)+1;
            }


            if(column < 0 || row < 0)
            {
                qDebug()<<"column or row is error!"<<endl;
            }

            if(!eleLayout->isEmpty())
            {
                //现有的控件不必清空,只是对现有的控件进行排序,空Widget每次都要清空
                for(int i = 0;i < 5;i++)
                {
                    eleLayout->removeWidget(&spaceWidget[i]);
                }

            }

            //对软件控件进行重新排序
            int num=0;
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<column;j++)
                {

                    eleLayout->addWidget(moreElement[num].baseWidget,i,j,1,1,Qt::AlignLeft);

                    if(num<(numElement-1))
                    {
                        num++;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            //为不够一行的软件类添加空控件，使布局好看
            for(int i = 0;i<(column - numElement);++i)
            {
                eleLayout->addWidget(&spaceWidget[i],0,numElement+i,1,1,Qt::AlignLeft);
            }

            //隐藏多余的控件
            if(numElement>column)
            {
                for(int i = numElement;i<MAXNUMBER;i++)
                {

                    moreElement[i].baseWidget->hide();
                }
                for(int i = 0;i<numElement;i++)
                {

                    moreElement[i].baseWidget->show();
                }
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}
