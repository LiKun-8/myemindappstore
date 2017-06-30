#include "custombutton.h"
#include <QDebug>
#include <QToolTip>
CustomButton::CustomButton()
{

}

CustomButton::~CustomButton()
{

}

void CustomButton::enterEvent(QEvent *)
{
    setStyleSheet("QPushButton{background: dodgerblue;}");
}

void CustomButton::leaveEvent(QEvent *)
{
    setStyleSheet("QPushButton{background: none;}");
}

