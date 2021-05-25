#include "robotpigswidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RobotPigsWidget w;
    w.show();
    return a.exec();
}
