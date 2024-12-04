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
    traversalSequence.clear();

    // Start Inorder Traversal
    tree->startTraversal("Inorder", [this](QString value) {
        traversalStep(value);
    });
}

void MainWindow::on_buttonPreorderTraversal_clicked() {
    ui->labelTraversalOutput->clear();
    traversalSequence.clear();

    // Start Preorder Traversal
    tree->startTraversal("Preorder", [this](QString value) {
        traversalStep(value);
    });
}

void MainWindow::on_buttonPostorderTraversal_clicked() {
    ui->labelTraversalOutput->clear();
    traversalSequence.clear();

    // Start Postorder Traversal
    tree->startTraversal("Postorder", [this](QString value) {
        traversalStep(value);
    });
}

void MainWindow::traversalStep(QString value) {
    traversalSequence += value + " ";
    ui->labelTraversalOutput->setText(traversalSequence);

    // Find the node in the graphics scene and highlight it
    auto node = findGraphicsNode(value);
    if (node) {
        node->setBrush(QBrush(Qt::yellow)); // Highlight the node with yellow color

        // Revert the color back to the original after 500ms
        QTimer::singleShot(500, [node]() {
            node->setBrush(QBrush(Qt::lightGray)); // Reset to the default color
        });
    }
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

