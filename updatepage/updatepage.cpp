#include <QHeaderView>
#include <QDebug>
#include <QLoggingCategory>
#include <packagekitqt5/PackageKit/Transaction>
#include "updatepage.h"

UpdatePage::UpdatePage(QWidget *parent) : QWidget(parent)
{
    upd = new PkUpdates(this);
    upd->checkUpdates();

    createUpdateWindow();
}

void UpdatePage::createUpdateWindow()
{
    upScroArea = new QScrollArea(this);
    upScroArea->resize(960,640);
    upScroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    upScroArea->setFrameShape(QFrame::NoFrame);
    pageUpdateWidget = new QWidget();

    updateTable = new QTableWidget(this);
//    updateTable->setBaseSize(960,640);
    updateTable->setShowGrid(false);
    updateTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateTable->setFrameShape(QFrame::NoFrame);
    updateTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    updateTable->setFocusPolicy(Qt::NoFocus);

    updTaskBar = new TaskBar(this,"0个应用可升级","全部更新");
    connect(upd,SIGNAL(getUpdFinished(QStringList)),this,SLOT(onGetupFinished(QStringList)));

    upVLayout = new QVBoxLayout();
    upVLayout->setMargin(16);
    upVLayout->addWidget(updTaskBar);
    upVLayout->addWidget(updateTable);
    this->setLayout(upVLayout);

    pageUpdateWidget->setLayout(upVLayout);
    upScroArea->setWidget(pageUpdateWidget);
    upScroArea->setWidgetResizable(true);
}

void UpdatePage::onGetupFinished(QStringList nameList)
{
    qDebug() << endl << __FUNCTION__ ;
    int rowCount = nameList.length();
    qDebug() << "rowCount:" << rowCount ;
    QString countStr = QString::number(rowCount, 10);
    QString upStr = countStr + "个应用可升级" ;
    updTaskBar->setTaskLabel(upStr);
    updateTable->setColumnCount(1);
    updateTable->setRowCount(rowCount);

//    updateTable->resizeColumnToContents(0);
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

    for(int i = 0; i < rowCount; i++)
    {
        QString appName =  nameList.at(i);
//        qDebug() << "appName : " << appName;
        AppWidget* appWidget = new AppWidget(this,appName);
        updateTable->setCellWidget(i,0,appWidget);

        connect(appWidget->headButton,SIGNAL(clicked()),this,SLOT(pageUpdateBtnClicked()));
        connect(appWidget->nameButton,SIGNAL(clicked()),this,SLOT(pageUpdateBtnClicked()));
        connect(appWidget->funcButton,SIGNAL(clicked()),this,SLOT(pageUpdateBtnClicked()));
        connect(appWidget->updateButton,SIGNAL(clicked()),this,SLOT(pageUpdateBtnClicked()));
        connect(appWidget,SIGNAL(sigIntroResize()),this,SLOT(strLenChanged()));
    }
    updateTable->setRowHeight(0,95);
    updateTable->setRowHeight(0,96);
}

void UpdatePage::pageUpdateBtnClicked()
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

            connect(nfuncWidget->hideButton,SIGNAL(clicked()),this,SLOT(pageUpdateBtnClicked()));
            connect(nfuncWidget,SIGNAL(sigTextHeight(int)),this,SLOT(textAreaChanged(int)));

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

void UpdatePage::strLenChanged()
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

void UpdatePage::textAreaChanged(int hig)
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

bool UpdatePage::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        upScroArea->resize(QSize(this->width(),this->height()));
        return true;
    }
    return QWidget::event(event);
}



