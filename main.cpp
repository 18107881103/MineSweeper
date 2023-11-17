#include "widget.h"
#include "loginwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    LoginWidget w2;
    w2.show();


    return a.exec();
}
