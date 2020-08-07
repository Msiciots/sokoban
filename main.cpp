#include "mainwindow.h"
#include "menu.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Menu menu;
    menu.show();
    

    return a.exec();
}
