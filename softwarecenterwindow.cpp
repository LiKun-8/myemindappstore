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
    pageUpdate = new QWidget();
    pageManager = new QWidget();
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
    CreateUpdateWindow();
    CreateManagerWindow();
}

void SoftwareCenterWindow::CreateUpdateWindow()
{
    upScroArea = new QScrollArea(pageUpdate);
    upScroArea->resize(this->width(),this->height());
    upScroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    upScroArea->setFrameShape(QFrame::NoFrame);
    pageUpdateWidget = new QWidget();

    updTaskBar = new TaskBar(0,"5个应用可升级","全部更新");
    updateTable = new QTableWidget(this);
    int rowCount = 12;
    updateTable->setColumnCount(1);
    updateTable->setRowCount(rowCount);
    updateTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateTable->setFrameShape(QFrame::NoFrame);
    updateTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    updateTable->setFocusPolicy(Qt::NoFocus);
    updateTable->resizeColumnToContents(0);
    updateTable->setShowGrid(false);
    updateTable->setStyleSheet(
                "QTableWidget {"
                "background-color: #00000000;"
                "}"
                "QTableWidget::item {"
                "border-top: 1px solid #dcdcdc;"
                "}"
                "QTableWidget::item:selected{"
                "background: white;"
                "}"
                );
    updateTable->verticalHeader()->setDefaultSectionSize(96);
    updateTable->horizontalHeader()->setStretchLastSection(true);
    updateTable->setFrameStyle(QFrame::NoFrame);

    updateTable->setMinimumHeight(96*rowCount);

    QHeaderView* vheaderView = updateTable->verticalHeader();
    vheaderView->setHidden(true);
    QHeaderView *hheaderView = updateTable->horizontalHeader();
    hheaderView->setHidden(true);

    for(int i = 0; i < updateTable->rowCount(); i++)
    {
        AppWidget* appWidget = new AppWidget();
        updateTable->setCellWidget(i,0,appWidget);

        connect(appWidget->headButton,SIGNAL(clicked()),this,SLOT(PageUpdateBtnClicked()));
        connect(appWidget->nameButton,SIGNAL(clicked()),this,SLOT(PageUpdateBtnClicked()));
        connect(appWidget->funcButton,SIGNAL(clicked()),this,SLOT(PageUpdateBtnClicked()));
        connect(appWidget->updateButton,SIGNAL(clicked()),this,SLOT(PageUpdateBtnClicked()));
        connect(appWidget,SIGNAL(sigIntroResize()),this,SLOT(StrLenChanged()));
    }

    upVLayout = new QVBoxLayout();
    upVLayout->setMargin(16);
    upVLayout->addWidget(updTaskBar);
    upVLayout->addWidget(updateTable);
    pageUpdate->setLayout(upVLayout);

    pageUpdateWidget->setLayout(upVLayout);
    upScroArea->setWidget(pageUpdateWidget);
    upScroArea->setWidgetResizable(true);

}


void SoftwareCenterWindow::PageUpdateBtnClicked()
{
    for(int i = 0; i < updateTable->rowCount(); i++)
    {
        AppWidget* appWidget = (AppWidget*)updateTable->cellWidget(i,0);

        if(sender() == appWidget->headButton )
        {
            //            qDebug() << "btn == headButton:" << "row == " << i;
            break;
        }
        else if(sender() == appWidget->nameButton)
        {
            //            qDebug() << "btn == nameButton:" << "row == " << i;
            break;
        }
        else if(sender() == appWidget->funcButton)
        {
            int tableHeight = updateTable->height();

            updateTable->insertRow(i+1);
            FuncWidget *nfuncWidget = new FuncWidget();
            updateTable->setCellWidget(i+1,0,nfuncWidget);
            int textHeight  = nfuncWidget->nfuncEdit->document()->size().height();
            int rowHeight = textHeight+20+16+18+22;
            updateTable->setRowHeight(i+1,rowHeight);
            appWidget->funcButton->setEnabled(false);
            updateTable->setMinimumHeight(tableHeight + rowHeight);

            connect(nfuncWidget->hideButton,SIGNAL(clicked()),this,SLOT(PageUpdateBtnClicked()));
            connect(nfuncWidget,SIGNAL(sigTextHeight(int)),this,SLOT(TextAreaChanged(int)));

            break;
        }
        else if(sender() == appWidget->updateButton)
        {
            //            qDebug() << "btn == updateButton:" << "row == " << i;
            break;
        }
        else
        {
            FuncWidget* gfuncWidget = (FuncWidget*)updateTable->cellWidget(i,0);
            if(sender() == gfuncWidget->hideButton)
            {
                //                qDebug() << "btn == hideButton:" << "row == " << i;
                int rmvTableHeight = updateTable->height();
                int rmvRowHeight = updateTable->rowHeight(i);
                int tableHeight = rmvTableHeight - rmvRowHeight;
                AppWidget *eblBtnWid = (AppWidget *)updateTable->cellWidget(i-1,0);
                eblBtnWid->funcButton->setEnabled(true);
                updateTable->removeRow(i);
                updateTable->setMinimumHeight(tableHeight);
            }
        }
    }
}

void SoftwareCenterWindow::StrLenChanged()
{
    for(int i = 0; i < updateTable->rowCount(); i++)
    {
        AppWidget* chLabelWidth = (AppWidget*)updateTable->cellWidget(i,0);
        if(sender() == chLabelWidth)
        {
            chLabelWidth->introLabel->setText(chLabelWidth->introstr);
            int labelWidth = chLabelWidth->introLabel->width();
            QFont font;
            QFontMetrics fm(font);
            int fontSize = fm.width(chLabelWidth->introstr);
            QString fmstr = chLabelWidth->introstr;
            labelWidth = updateTable->width() -520;
            if(labelWidth > 550)
            {
                labelWidth = 550;
            }
            if(fontSize > labelWidth)
            {
                fmstr = fm.elidedText(chLabelWidth->introstr, Qt::ElideRight, labelWidth - 70);

            }
            chLabelWidth->introLabel->setText(fmstr);
        }
    }
}

void SoftwareCenterWindow::TextAreaChanged(int hig)
{
    for(int i = 0; i < updateTable->rowCount(); i++)
    {
        FuncWidget* chEditHeight = (FuncWidget*)updateTable->cellWidget(i,0);
        if(sender() == chEditHeight)
        {
            int rowHeight = hig+20+16+18+22;
            updateTable->setRowHeight(i,rowHeight);
        }
    }
}

void SoftwareCenterWindow::CreateManagerWindow()
{
    manScroArea = new QScrollArea(pageManager);
    manScroArea->resize(this->width(),this->height());
    manScroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    manScroArea->setFrameShape(QFrame::NoFrame);

    QString strtask = "进行中的任务 ";
    QString stronekey =  "全部开始";

    QWidget *wid = new QWidget();

    manTaskBar = new TaskBar(this,strtask,stronekey);

    installTable = new QTableWidget();
    installTable->setColumnCount(1);
    installTable->setRowCount(5);
    installTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    installTable->setFrameShape(QFrame::NoFrame);
    installTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    installTable->setFocusPolicy(Qt::NoFocus);
    installTable->resizeColumnToContents (0);
    installTable->setShowGrid(false);
    installTable->setStyleSheet(
                "QTableWidget {"
                "background-color: #00000000;"
                "}"
                "QTableWidget::item {"
                "border-top: 1px solid #dcdcdc;"
                "}"
                "QTableWidget::item:selected{"
                "background-color: white;"
                "}"
                );
    installTable->verticalHeader()->setDefaultSectionSize(96);
    installTable->horizontalHeader()->setStretchLastSection(true);
    QHeaderView* vheaderView = installTable->verticalHeader();
    vheaderView->setHidden(true);
    QHeaderView *hheaderView = installTable->horizontalHeader();
    hheaderView->setHidden(true);

    int rowCount = installTable->rowCount();
    installTable->setMinimumHeight(96*rowCount);

    for(int i = 0; i < rowCount; i++)
    {
        ManagerWidget *manTaskManager = new ManagerWidget(this,"QQ","版本:0.8.3","大小:25.8M");
        manTaskManager->GetButton(1)->hide();
        installTable->setCellWidget(i,0,manTaskManager);
    }

    splitLabel = new QLabel();
    splitLabel->size().setHeight(16);
    splitLabel->setStyleSheet("background: #f9f9f9;");

    QString strtask1 = "已完成的任务 ";
    QString stronekey1 =  "";
    manCompBar = new TaskBar(this,strtask1,stronekey1);
    manCompBar->hideOnekeyButton();
    manCompBar->size().setHeight(64);

    compTable = new QTableWidget();
    compTable = new QTableWidget();
    compTable->setColumnCount(1);
    compTable->setRowCount(10);
    compTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    compTable->setFrameShape(QFrame::NoFrame);
    compTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    compTable->setFocusPolicy(Qt::NoFocus);
    compTable->resizeColumnToContents (0);
    compTable->setShowGrid(false);
    compTable->setStyleSheet(
                "QTableWidget {"
                "background-color: #00000000;"
                "}"
                "QTableWidget::item {"
                "border-top: 1px solid #dcdcdc;"
                "}"
                "QTableWidget::item:selected{"
                "background:white;"
                "}"
                );
    compTable->verticalHeader()->setDefaultSectionSize(96);
    compTable->horizontalHeader()->setStretchLastSection(true);
    QHeaderView* vheaderView1 = compTable->verticalHeader();
    vheaderView1->setHidden(true);
    QHeaderView *hheaderView1 = compTable->horizontalHeader();
    hheaderView1->setHidden(true);

    int compRowCount = compTable->rowCount();
    compTable->setMinimumHeight(96*compRowCount);

    for(int j = 0; j < compRowCount; j++)
    {
        ManagerWidget *manTaskManager = new ManagerWidget(this,"微信","版本:0.2.6","大小:66.8M");
        manTaskManager->GetButton(2)->setText(tr("Open"));
        compTable->setCellWidget(j,0,manTaskManager);
    }

    vboxLayout = new QVBoxLayout();
    vboxLayout->setMargin(0);
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setContentsMargins(16,0,16,0);
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setContentsMargins(16,0,16,0);

    vboxLayout->addLayout(vboxLayout1);
    vboxLayout1->addWidget(manTaskBar);
    vboxLayout1->addWidget(installTable);
    vboxLayout->addWidget(splitLabel);
    vboxLayout->addLayout(vboxLayout2);
//    vboxLayout->addSpacing(0);
    vboxLayout2->addSpacing(24);
    vboxLayout2->addWidget(manCompBar);
    vboxLayout2->addSpacing(24);
    vboxLayout2->addWidget(compTable);
//    vboxLayout->addStretch();

    wid->setLayout(vboxLayout);
    manScroArea->setWidget(wid);
    manScroArea->setWidgetResizable(true);

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
        scrollClass->resize(stwWindow->size().width(),stwWindow->size().height());
        upScroArea->resize(stwWindow->size().width(),stwWindow->size().height());
        manScroArea->resize(stwWindow->size().width(),stwWindow->size().height());

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
    upScroArea->resize(stwWindow->size().width(),stwWindow->size().height());
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


