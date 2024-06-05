#include "mainwindow.h"

#include <QApplication>
#include <QVariant>
#include "qbootstrap.h"
#include "elementstyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto elementStyle = new ElementStyle(a.style());
    a.setStyle(elementStyle);
    MainWindow w;
    w.show();
    return a.exec();
}
