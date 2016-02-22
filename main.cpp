#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	//was used for easy stub testing, ignore
    /*argc = 3;
    argv[1] = "~/Downloads/shirt_1.output";
    argv[2] = "~/Downloads/dog_1.output";*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
