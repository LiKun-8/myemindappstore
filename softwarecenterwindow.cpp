#include "softwarecenterwindow.h"
#include <QDebug>
#include <QHeaderView>

SoftwareCenterWindow::SoftwareCenterWindow(QWidget *parent)
    : QWidget(parent)
{
    this->resize(960,640);
    hbLayout = new QHBoxLayout();
    vbLayout = new QVBoxLayout();
    hbBtnLayout = new QHBoxLayout();
    hbBtnLayout->setSpacing(48);
    setStyleSheet("background: white;");

    //初始化窗口
    InitMainWindow();

    //上部布局
    hbLayout->addWidget(btnReturn);
    hbLayout->addWidget(btnNext);
    hbLayout->addWidget(btnRefresh);
    hbLayout->addSpacerItem(leftSpace);
    hbBtnLayout->addWidget(btnHome);
    hbBtnLayout->addWidget(btnClass);
    hbBtnLayout->addWidget(btnUpdate);
    hbBtnLayout->addWidget(btnManager);
    hbLayout->addLayout(hbBtnLayout);
    hbLayout->addSpacerItem(rightSpace);
    hbLayout->addWidget(lineSearch);
    hbLayout->setSpacing(20);
    hbLayout->setMargin(16);

    //整体布局
    vbLayout->addLayout(hbLayout);
    vbLayout->addWidget(stwWindow);
    vbLayout->setMargin(0);
    vbLayout->setSpacing(0);
    this->setLayout(vbLayout);

    connect(btnHome,SIGNAL(clicked(bool)),this,SLOT(OnBtnHome()));
    connect(btnClass,SIGNAL(clicked(bool)),this,SLOT(OnBtnClass()));
    connect(btnUpdate,SIGNAL(clicked(bool)),this,SLOT(OnBtnUpdate()));
    connect(btnManager,SIGNAL(clicked(bool)),this,SLOT(OnBtnManager()));
}

SoftwareCenterWindow::~SoftwareCenterWindow()
{
}

void SoftwareCenterWindow::InitMainWindow()
{
    btnReturn = new QPushButton();
    btnReturn->setFixedSize(36,36);
    btnReturn->setStyleSheet("background-image:url(:/image/return.png);");
    btnNext = new QPushButton();
    btnNext->setFixedSize(36,36);
    btnNext->setStyleSheet("background-image:url(:/image/next.png);");
    btnRefresh = new QPushButton();
    btnRefresh->setFixedSize(36,36);
    btnRefresh->setStyleSheet("background-image:url(:/image/refresh.png);");
    btnHome = new QPushButton();
    btnHome->setText("HOME");
    btnHome->setFixedSize(80,24);
    btnClass = new QPushButton();
    btnClass->setText("CLASS");
    btnClass->setFixedSize(80,24);
    btnUpdate = new QPushButton();
    btnUpdate->setText("UPDATE");
    btnUpdate->setFixedSize(80,24);
    btnManager = new QPushButton();
    btnManager->setText("MANAGER");
    btnManager->setFixedSize(80,24);

    //隐藏按钮边框
    btnReturn->setFlat(true);
    btnNext->setFlat(true);
    btnRefresh->setFlat(true);
    btnHome->setFlat(true);
    btnClass->setFlat(true);
    btnUpdate->setFlat(true);
    btnManager->setFlat(true);

    leftSpace = new QSpacerItem(24, 48,QSizePolicy::Expanding);
    rightSpace = new QSpacerItem(24,48,QSizePolicy::Expanding,QSizePolicy::Minimum);

    lineSearch = new QLineEdit();
    lineSearch->setFixedSize(160,24);
    lineSearch->setPlaceholderText("please input text");

    stwWindow = new QStackedWidget(this);
    stwWindow->setMaximumWidth(1200);

    pageHome = new QWidget();
    pageClass = new QWidget();
    pageUpdate = new UpdatePage();
    pageManager = new ManagerPage();
    pageMore = new QWidget();

    stwWindow->addWidget(pageHome);
    stwWindow->addWidget(pageClass);
    stwWindow->addWidget(pageUpdate);
    stwWindow->addWidget(pageManager);
    stwWindow->addWidget(pageMore);

    label1 = new QLabel(pageHome);
    label1->setText("HOME");
    label2 = new QLabel(pageClass);
    label2->setText("CLASS");

    btnHome->setFocusPolicy(Qt::NoFocus);
    btnManager->setFocusPolicy(Qt::NoFocus);
    btnNext->setFocusPolicy(Qt::NoFocus);
    btnRefresh->setFocusPolicy(Qt::NoFocus);
    btnReturn->setFocusPolicy(Qt::NoFocus);
    btnClass->setFocusPolicy(Qt::NoFocus);
    btnUpdate->setFocusPolicy(Qt::NoFocus);

    vbClasslayoutMore = new QVBoxLayout();
    moreClassWidget = new ShowMore();
    scrollClass = new QScrollArea(pageClass);
    scrollMore = new QScrollArea(pageMore);

    CreateClassWindow();
    CreateMorewindow();
}


void SoftwareCenterWindow::CreateClassWindow()
{
    int catenum = 4;
    classWidget = new ClassWidget[catenum];
    vbClasslayout = new QVBoxLayout();
    pageClassWidget = new QWidget();

    vbClasslayout = new QVBoxLayout();
    scrollClass->setFrameShape(QFrame::NoFrame); //去除窗口边框

    for(int i=0;i<catenum;i++)
    {
        connect(&classWidget[i],SIGNAL(moreShow(int)),this,SLOT(SetMoreShow(int)));
        classWidget[i].setCategory(i);
        classWidget[i].setTopName();
        vbClasslayout->addWidget(classWidget[i].widget);
    }

    for(int i = 0;i<catenum;i++)
    {
        classWidget[i].initElement();
    }

    pageClassSpacer =new QSpacerItem(24,24,QSizePolicy::Minimum,QSizePolicy::Expanding);
    scrollClass->setWidget(pageClassWidget);
    vbClasslayout->addSpacerItem(pageClassSpacer);
    vbClasslayout->setMargin(0);
    pageClassWidget->setLayout(vbClasslayout);
    //滚动条不可见，只能通过鼠标滑动
    scrollClass->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollClass->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollClass->setWidgetResizable(true);
}



void SoftwareCenterWindow::CreateMorewindow()
{
    pageMoreWidget = new QWidget();
    vbClasslayoutMore = new QVBoxLayout();
    scrollMore->setFrameShape(QFrame::NoFrame); //去除窗口边框
    vbClasslayoutMore->addWidget(moreClassWidget->moreWidget);

    pageMoreSpacer =new QSpacerItem(24,24,QSizePolicy::Minimum,QSizePolicy::Expanding);
    scrollMore->setWidget(pageMoreWidget);
    vbClasslayoutMore->addSpacerItem(pageMoreSpacer);
    vbClasslayoutMore->setMargin(0);
    pageMoreWidget->setLayout(vbClasslayoutMore);
    //滚动条不可见，只能通过鼠标滑动
    scrollMore->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollMore->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollMore->setWidgetResizable(true);
}

bool SoftwareCenterWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        StwwindowMove();

        return true;
    }
    return QWidget::event(event);
}

void SoftwareCenterWindow::StwwindowMove()
{
    stwWindow->move((this->size().width()-stwWindow->size().width())/2,72);
}

void SoftwareCenterWindow::OnBtnHome()
{
    SetCurrentPage(HOMEPAGE);
}

void SoftwareCenterWindow::OnBtnClass()
{
    SetCurrentPage(CLASSPAGE);
    scrollClass->resize(stwWindow->size().width(),stwWindow->size().height());
}

void SoftwareCenterWindow::OnBtnUpdate()
{
    SetCurrentPage(UPDATEPAGE);
//    upScroArea->resize(stwWindow->size().width(),stwWindow->size().height());
}

void SoftwareCenterWindow::OnBtnManager()
{

    SetCurrentPage(MANAGERPAGE);
}

void SoftwareCenterWindow::SetMoreShow(int category)
{
    SetCurrentPage(MOREPAGE);
    scrollMore->resize(stwWindow->size().width(),stwWindow->size().height());
}

//跳转指定页面
void SoftwareCenterWindow::SetCurrentPage(int page)
{
    stwWindow->setCurrentIndex(page);
    StwwindowMove();
}


