#include "appwidget.h"
#include <QDebug>
#include <QPalette>
#include <QEvent>

//#define SIZE_W 250

AppWidget::AppWidget(QWidget *parent,QString namestr) : QWidget(parent)
{
    appLayout = new QHBoxLayout();
    appLayout->setMargin(0);
    rightLayout = new QVBoxLayout();
    rightLayout->setMargin(0);
    bottomLayout = new QHBoxLayout();

    headButton = new QPushButton();
    QPixmap pixmap("updatepage/image/head.png");
    headButton->setFlat(true);
    headButton->setIcon(pixmap);
    headButton->setIconSize(QSize(64,64));

    nameButton = new QPushButton();
    nameButton->setFlat(true);
    nameButton->setMaximumWidth(180);
    nameButton->setStyleSheet("text-align: left;");
    nameButton->setText(namestr);

    introstr = "全新视觉，简约界面乐享沟通！全新视觉，简约界面乐享沟通！全新视觉，简约界面乐享沟通！全新视觉，简约界面乐享沟通！";

    introLabel = new QLabel();
    introLabel->size().setWidth(20);

    introLabel->setStyleSheet("border-right: 1px; border-style: solid; border-color: #cccccc;");
    introLabel->setText(introstr);

    funcButton = new QPushButton();
    funcButton->setFlat(true);
    funcButton->setText(tr("新版功能"));
    funcButton->setFlat(true);
    QPalette fucpal;
    fucpal.setColor(QPalette::ButtonText, QColor(2,122,255));
    funcButton->setPalette(fucpal);
    funcButton->setStyleSheet("text-align: left;");
    funcButton->setMaximumWidth(64);

    sizeLabel = new QLabel();
    sizeLabel->resize(16,64);
    sizeLabel->setText(tr("13.8M"));

    versionLabel = new QLabel();
    versionLabel->setText(tr("V7.0.0"));

    updateButton = new QPushButton();
    updateButton->setFixedSize(80,32);
//    QPalette uppal;
//    uppal.setColor(QPalette::ButtonText, QColor(2,122,255));
//    updateButton->setPalette(uppal);
//    updateButton->setStyleSheet("border: 1px solid #027aff  ; border-radius: 2px; ");
//    updateButton->setStyleSheet("border-color: #027aff; border-width: 1px; border-style: solid; border-radius: 2px; ");
    updateButton->setText(tr("update"));

    appLayout->addWidget(headButton);
    appLayout->setSpacing(16);
    appLayout->addLayout(rightLayout);
    rightLayout->addStretch(24);
    rightLayout->addWidget(nameButton);
    rightLayout->setSpacing(3);
    rightLayout->addLayout(bottomLayout);
    rightLayout->addStretch(24);
    bottomLayout->addWidget(introLabel);
    bottomLayout->addWidget(funcButton);
    bottomLayout->addStretch();
    appLayout->addWidget(sizeLabel);
    appLayout->addSpacing(112);
    appLayout->addWidget(versionLabel);
    appLayout->addSpacing(112);
    appLayout->addWidget(updateButton);
    setLayout(appLayout);
}

bool AppWidget::event(QEvent *event)
{
    if(event->type() == QEvent::Resize )
    {
        emit sigIntroResize();
        return true;
    }
    return QWidget::event(event);
}



