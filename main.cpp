#include "mainwindow.h"

#include <QApplication>
#include <QVariant>
#include "qbootstrap.h"
#include "elementstyle.h"

int main(int argc, char *argv[])
{
    auto elementStyle = new ElementStyle;
    QApplication a(argc, argv);
    a.setStyle(elementStyle);
    MainWindow w;
    w.show();
    return a.exec();
}
