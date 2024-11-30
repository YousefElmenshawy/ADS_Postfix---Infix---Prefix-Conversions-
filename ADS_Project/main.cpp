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
    QString PostfixExpression = "13 4 +";
    QString InfixExpression= " 1+2*3/(6+7)";
    QString PrefixExpression = "+ + * 3 4 - 5 2 7";
    cerr << "Building tree for: " << PostfixExpression.toStdString() << endl;

    Tree.buildfromPostfix(PostfixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Infix Expression: " << Tree.ToInfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }
    Tree.reset();
    cerr << "Building tree for: " << InfixExpression.toStdString() << endl;

    Tree.buildfromInfix(InfixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Postfix Expression: " << Tree.ToPostfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }
    Tree.reset();
    cerr << "Building tree for: " << PrefixExpression.toStdString() << endl;

    Tree.buildfromPrefix(PrefixExpression);
    if (Tree.Root_Accesser()) {
        cerr << "Postfix Expression: " << Tree.ToPostfix(Tree.Root_Accesser()).toStdString() << endl;
    } else {
        cerr << "Error: Tree was not constructed!" << endl;
    }



    return a.exec();

}
