#include "expressiontree.h"
#include "TreeNode.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Create ExpressionTree
    ExpressionTree tree;

    // Example: Build tree from a postfix expression
    QString postfix = "3 4 + 5 * 6 +";
    tree.buildfromPostfix(postfix);

    // Create a scene for visualization
    QGraphicsScene scene;

    // Visualize the tree starting from the root
    tree.visualizeTree(&scene, tree.Root_Accesser(), 400, 50, 200, 100);

    // Create a view and display the scene
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle("Expression Tree Visualization");
    view.resize(800, 600);
    view.show();

    return app.exec();
}
