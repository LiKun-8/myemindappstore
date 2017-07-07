#include <QHeaderView>
#include "updatepage.h"

UpdatePage::UpdatePage(QWidget *parent) : QWidget(parent)
{
       CreateUpdateWindow();
}

void UpdatePage::CreateUpdateWindow()
{
    upScroArea = new QScrollArea(this);
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
    this->setLayout(upVLayout);

    pageUpdateWidget->setLayout(upVLayout);
    upScroArea->setWidget(pageUpdateWidget);
    upScroArea->setWidgetResizable(true);

}


void UpdatePage::PageUpdateBtnClicked()
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

void UpdatePage::StrLenChanged()
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

void UpdatePage::TextAreaChanged(int hig)
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


