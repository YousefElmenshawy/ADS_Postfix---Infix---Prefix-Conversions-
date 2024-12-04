#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QString>
#include "expressiontree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Button handlers for building and traversing the tree
    void on_buttonBuildTree_clicked();
    void on_buttonInorderTraversal_clicked();
    void on_buttonPreorderTraversal_clicked();
    void on_buttonPostorderTraversal_clicked();

private:
    // Helper methods
    void traversalStep(QString value);
    QGraphicsEllipseItem* findGraphicsNode(const QString& value);

    // UI and data members
    Ui::MainWindow *ui;
    ExpressionTree *tree; // Expression tree instance
    QString traversalSequence; // Stores traversal output
};

#endif // MAINWINDOW_H
