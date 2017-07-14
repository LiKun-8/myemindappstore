 #include "managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent,QString namestr, QString verstr, QString sizestr) : QWidget(parent)
{    
    hbLayout = new QHBoxLayout();
    hbLayout->setMargin(0);
    vbLayout = new QVBoxLayout();
    vbLayout->setMargin(0);

    headButton = new QPushButton();
    headButton = new QPushButton();
    QPixmap pixmap(tr("updatepage/image/head.png"));
    headButton->setFlat(true);
    headButton->setIcon(pixmap);
    headButton->setIconSize(QSize(64,64));


    nameButton = new QPushButton();
    nameButton->setFlat(true);
    nameButton->setMaximumWidth(100);
    nameButton->setStyleSheet("text-align: left;");
    nameButton->setText(namestr);

    verLabel = new QLabel();
    verLabel->setText(verstr);

    sizeLabel = new QLabel();
    sizeLabel->setText(sizestr);

    uninsButton = new QPushButton();
    uninsButton->setText(tr("uninstall"));
    uninsButton->setFixedSize(80,32);

    managerButton = new QPushButton();
    managerButton->setText(tr("正在安装"));
    managerButton->setFixedSize(80,32);

    hbLayout->addWidget(headButton);
    hbLayout->addSpacing(5);
    hbLayout->addLayout(vbLayout);
    hbLayout->addStretch();
    hbLayout->addWidget(uninsButton);
    hbLayout->addWidget(managerButton);

    vbLayout->addStretch();
    vbLayout->addWidget(nameButton);
    vbLayout->addSpacing(3);
    vbLayout->addWidget(verLabel);
    vbLayout->addSpacing(0);
    vbLayout->addWidget(sizeLabel);
    vbLayout->addStretch();

    setLayout(hbLayout);
}

QPushButton * ManagerWidget::GetButton(int num)
{
    switch (num) {
    case 1:
        return uninsButton;
    case 2:
        return managerButton;
    default:
        break;
    }
}

void ManagerWidget::setManagerButton(QString manastr)
{
    managerButton->setText(manastr);
}
