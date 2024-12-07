#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expressiontree.h"
#include <QTimer>
#include<QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tree(new ExpressionTree()),scene(new QGraphicsScene(this)) // Initialize the expression tree
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: grey;");
    ui->graphicsViewTree->setScene(scene);
    connect(tree, &ExpressionTree::updateTraversalOutput, this, &MainWindow::updateTraversalLabel);
}

MainWindow::~MainWindow() {
    delete ui;
    delete tree;
    delete scene;
}

void MainWindow::on_buttonBuildTree_clicked() {
    QString expression = ui->lineEditExpression->text();
    QString type = ui->comboBoxExpressionType->currentText();

    try {
        if (type == "Infix") {
            tree->buildfromInfix(expression);

           ui->EvaluateLabel->setText( QString::number(tree->evaluateExpression()));
        } else if (type == "Prefix") {
            tree->buildfromPrefix(expression);
            double Result = tree->evaluateExpression();
                            QString Result2 = QString::number(Result);
             ui->EvaluateLabel->setText(Result2);
        } else if (type == "Postfix") {
            tree->buildfromPostfix(expression);
             ui->EvaluateLabel->setText( QString::number(tree->evaluateExpression()));
        }

        // Clear the QGraphicsScene
        scene = new QGraphicsScene(this);
        ui->graphicsViewTree->setScene(scene);

        // Visualize the tree
        tree->visualizeTree(scene, tree->Root_Accesser(), 400, 50, 200, 100);
        ui->labelTraversalOutput->clear(); // Clear traversal output
    } catch (const std::exception &e) {
        ui->labelTraversalOutput->setText(QString("Error: %1").arg(e.what()));
    }
}

void MainWindow::on_buttonInorderTraversal_clicked() {

    QString traversalString;
    //scene = new QGraphicsScene(this);
    //ui->graphicsViewTree->setScene(scene);
   // ui->labelTraversalOutput->setText( traversalString);

    tree->animateTraversal(scene, tree->Root_Accesser(), "inorder", traversalString);
    //ui->labelTraversalOutput->clear();


}

void MainWindow::on_buttonPreorderTraversal_clicked() {

    QString traversalString;
    //scene = new QGraphicsScene(this);
    //ui->graphicsViewTree->setScene(scene);
     //ui->labelTraversalOutput->setText(traversalString);
    tree->animateTraversal(scene, tree->Root_Accesser(), "preorder", traversalString);
    //ui->labelTraversalOutput->clear();



}

void MainWindow::on_buttonPostorderTraversal_clicked() {

    QString traversalString;
   // ui->labelTraversalOutput->setText(traversalString);
    //scene = new QGraphicsScene(this);
    //ui->graphicsViewTree->setScene(scene);
    tree->animateTraversal(scene, tree->Root_Accesser(), "postorder", traversalString);
    //ui->labelTraversalOutput->clear();

}

void MainWindow::updateTraversalLabel(const QString& traversalString) {
    qDebug() << "Current traversal string: " << traversalString;
    qDebug() << "Label visible: " << ui->labelTraversalOutput->isVisible();
        ui->labelTraversalOutput->setText(traversalString);

}



