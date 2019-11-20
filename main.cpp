#include "mainwindow.h"
#include "mywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow window;
    window.show();
    return a.exec();
}
