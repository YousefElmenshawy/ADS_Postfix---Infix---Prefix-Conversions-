#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expressiontree.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tree(new ExpressionTree()) // Initialize the expression tree
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
}

MainWindow::~MainWindow() {
    delete ui;
    delete tree;
}

void MainWindow::on_buttonBuildTree_clicked() {
    QString expression = ui->lineEditExpression->text();
    QString type = ui->comboBoxExpressionType->currentText();

    try {
        if (type == "Infix") {
            tree->buildfromInfix(expression);
        } else if (type == "Prefix") {
            tree->buildfromPrefix(expression);
        } else if (type == "Postfix") {
            tree->buildfromPostfix(expression);
        }

        // Clear the QGraphicsScene
        auto scene = new QGraphicsScene(this);
        ui->graphicsViewTree->setScene(scene);

        // Visualize the tree
        tree->visualizeTree(scene, tree->Root_Accesser(), 400, 50, 200, 100);
        ui->labelTraversalOutput->clear(); // Clear traversal output
    } catch (const std::exception &e) {
        ui->labelTraversalOutput->setText(QString("Error: %1").arg(e.what()));
    }
}

void MainWindow::on_buttonInorderTraversal_clicked() {
    ui->labelTraversalOutput->clear();
    QString inoredered= tree->ToInfix(tree->Root_Accesser());
    ui->labelTraversalOutput->setText(inoredered);
}

void MainWindow::on_buttonPreorderTraversal_clicked() {
    ui->labelTraversalOutput->clear();
    QString preoredered= tree->ToPrefix(tree->Root_Accesser());
    ui->labelTraversalOutput->setText(preoredered);



}

void MainWindow::on_buttonPostorderTraversal_clicked() {
    ui->labelTraversalOutput->clear();
    QString postordered= tree->ToPostfix(tree->Root_Accesser());
    ui->labelTraversalOutput->setText(postordered);

}




QGraphicsEllipseItem* MainWindow::findGraphicsNode(const QString& value) {
    auto items = ui->graphicsViewTree->scene()->items();
    for (auto item : items) {
        auto ellipse = dynamic_cast<QGraphicsEllipseItem*>(item);
        if (ellipse) {
            // Check if this ellipse has a child text item with the matching value
            for (auto childItem : ellipse->childItems()) {
                auto textItem = dynamic_cast<QGraphicsTextItem*>(childItem);
                if (textItem && textItem->toPlainText() == value) {
                    return ellipse;
                }
            }
        }
    }
    return nullptr; // Return nullptr if the node is not found
}

