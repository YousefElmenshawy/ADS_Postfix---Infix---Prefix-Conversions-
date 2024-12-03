#include "mainwindow.h"
#include "expressiontree.h"
#include <QApplication>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
    //w.show();

    // Testing the program
    ExpressionTree Tree;
    Tree.displayConversionMenu(Tree);



    return a.exec();

}
