#include "funcwidget.h"
#include <QDebug>

FuncWidget::FuncWidget(QWidget *parent) : QWidget(parent)
{
    funcLayout = new QHBoxLayout;

    funcLayout->setMargin(0);
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    funcLabel = new QLabel();
    nfuncEdit = new QTextEdit();
    hideButton = new QPushButton();

    funcLabel->setText(tr(" 新版特性"));
    nfuncEdit->setText("- 全新皮肤引擎，全新视觉盛宴; \n- QQ大视频，视频聊天更大更清晰; \n- 聊天窗口个性动作，互动方式更多样; \n- QQ聊天装扮，聊天窗口与众不同;　\n- 空间编辑器新增记事本，双击头像直接开启;　\n- 自定义好友上线提醒，实时关注亲密好友;　\n- QQ锁独立密码，隐私保护更方便安全;　\n- 更换头像界面优化，自定义头像更换更便捷;");
    nfuncEdit->setStyleSheet("border: 0;" "background:white");
    nfuncEdit->setReadOnly(true);
    nfuncEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap pixmap(tr("updatepage/image/hide.png"));
    hideButton->setFlat(true);
    hideButton->setIcon(pixmap);
    hideButton->setIconSize(QSize(44,44));

    funcLayout->addSpacing(80);
    funcLayout->addLayout(leftLayout);
    leftLayout->addSpacing(20);
    leftLayout->addWidget(funcLabel);
    leftLayout->addSpacing(12);
    leftLayout->addWidget(nfuncEdit);
    leftLayout->addSpacing(24);
    funcLayout->addSpacing(100);
    funcLayout->addLayout(rightLayout);
    rightLayout->addStretch();
    rightLayout->addWidget(hideButton);
    rightLayout->addSpacing(10);
    funcLayout->addSpacing(10);
    setLayout(funcLayout);

}

bool FuncWidget::event(QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        int docheight = nfuncEdit->document()->size().height();
        emit sigTextHeight(docheight);
        return true;
    }
    return QWidget::event(event);
}
