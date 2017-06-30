#include "softwarecenterwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoftwareCenterWindow w;
    w.show();

    return a.exec();
}
