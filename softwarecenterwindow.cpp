#include "softwarecenterwindow.h"
#include <QFile>
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

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    this->setStyleSheet(style);
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
    pageClass = new ClassPage();
    pageUpdate = new UpdatePage();
    pageManager = new ManagerPage();

    stwWindow->addWidget(pageHome);
    stwWindow->addWidget(pageClass);
    stwWindow->addWidget(pageUpdate);
    stwWindow->addWidget(pageManager);
    stwWindow->addWidget(pageClass->moreClassWidget);

    btnHome->setFocusPolicy(Qt::NoFocus);
    btnManager->setFocusPolicy(Qt::NoFocus);
    btnNext->setFocusPolicy(Qt::NoFocus);
    btnRefresh->setFocusPolicy(Qt::NoFocus);
    btnReturn->setFocusPolicy(Qt::NoFocus);
    btnClass->setFocusPolicy(Qt::NoFocus);
    btnUpdate->setFocusPolicy(Qt::NoFocus);

    connect(pageClass,SIGNAL(setMore()),this,SLOT(onBtnMore()));
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

void SoftwareCenterWindow::onBtnMore()
{
    SetCurrentPage(MOREPAGE);
}

//跳转指定页面
void SoftwareCenterWindow::SetCurrentPage(int page)
{
    stwWindow->setCurrentIndex(page);
    StwwindowMove();
}


