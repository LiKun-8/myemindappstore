#include <QHeaderView>
#include "managerpage.h"

ManagerPage::ManagerPage(QWidget *parent) : QWidget(parent)
{
    updm = new PkUpdates(this);

    CreateManagerWindow();
}


void ManagerPage::CreateManagerWindow()
{
    manScroArea = new QScrollArea(this);
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

    connect(updm,SIGNAL(getInsFinished(QVariantMap)),this,SLOT(onGetInsFinished(QVariantMap)));

    int rowCount = installTable->rowCount();
    installTable->setMinimumHeight(96*rowCount);

    for(int i = 0; i < rowCount; i++)
    {
        ManagerWidget *manTaskManager = new ManagerWidget(this,"","QQ","版本:0.8.3","大小:25.8M");
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

void ManagerPage::onGetInsFinished(QVariantMap insdMap)
{
    qDebug() << __FUNCTION__;

    int insRowCount = insdMap.count();

    compTable->setColumnCount(1);
    compTable->setRowCount(insRowCount);
//    compTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

    compTable->setMinimumHeight(96*insRowCount);

    QVariantMap::iterator item;
    int count = 0;
    for(item = insdMap.begin(); item != insdMap.end(); item++)
    {
//        qDebug() << "item.value().proName" << ;
        QString appName = PackageKit::Transaction::packageName(item.key());
        QString appVersion = "版本 : " + PackageKit::Transaction::packageVersion(item.key());
        QString headUrl = item.value().toString();

//        QString appVersion = item.value().
        ManagerWidget *manTaskManager = new ManagerWidget(this,headUrl,appName,appVersion,"大小 : 66.8M");
        manTaskManager->GetButton(2)->setText(tr("Open"));
        compTable->setCellWidget(count,0,manTaskManager);
        count ++;
    }
}


bool ManagerPage::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        manScroArea->resize(QSize(this->width(),this->height()));
        return true;
    }
    return QWidget::event(event);

}


