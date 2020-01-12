
#include "mainwindow.h"
#include <QApplication>
#include <QScrollArea>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::CrossCursor);

    MainWindow w;
    w.show();

    return a.exec();
}


//#include <gtest/gtest.h>
//#include "mainwindow.h"
//#include <QApplication>
//#include <QScrollArea>
//using namespace ::testing;

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QApplication::setOverrideCursor(Qt::CrossCursor);


//    InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}

