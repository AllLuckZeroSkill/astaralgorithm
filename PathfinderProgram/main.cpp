#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Widget w;
    w.setStyleSheet("background-color: white;");

    w.show();
    return a.exec();
}
