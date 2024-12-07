/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *ImageLabel;
    QPushButton *buttonBuildTree;
    QLabel *label;
    QLineEdit *lineEditExpression;
    QComboBox *comboBoxExpressionType;
    QLabel *label_2;
    QPushButton *buttonInorderTraversal;
    QPushButton *buttonPreorderTraversal;
    QPushButton *buttonPostorderTraversal;
    QGraphicsView *graphicsViewTree;
    QLabel *labelTraversalOutput;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        ImageLabel = new QLabel(centralwidget);
        ImageLabel->setObjectName("ImageLabel");
        ImageLabel->setGeometry(QRect(250, 40, 800, 600));
        buttonBuildTree = new QPushButton(centralwidget);
        buttonBuildTree->setObjectName("buttonBuildTree");
        buttonBuildTree->setGeometry(QRect(160, 520, 62, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 490, 71, 20));
        lineEditExpression = new QLineEdit(centralwidget);
        lineEditExpression->setObjectName("lineEditExpression");
        lineEditExpression->setGeometry(QRect(110, 490, 151, 20));
        lineEditExpression->setStyleSheet(QString::fromUtf8("color: rgb(200, 9, 76)"));
        comboBoxExpressionType = new QComboBox(centralwidget);
        comboBoxExpressionType->addItem(QString());
        comboBoxExpressionType->addItem(QString());
        comboBoxExpressionType->addItem(QString());
        comboBoxExpressionType->setObjectName("comboBoxExpressionType");
        comboBoxExpressionType->setGeometry(QRect(80, 520, 71, 22));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 520, 41, 14));
        buttonInorderTraversal = new QPushButton(centralwidget);
        buttonInorderTraversal->setObjectName("buttonInorderTraversal");
        buttonInorderTraversal->setGeometry(QRect(380, 520, 62, 21));
        buttonPreorderTraversal = new QPushButton(centralwidget);
        buttonPreorderTraversal->setObjectName("buttonPreorderTraversal");
        buttonPreorderTraversal->setGeometry(QRect(300, 520, 62, 21));
        buttonPostorderTraversal = new QPushButton(centralwidget);
        buttonPostorderTraversal->setObjectName("buttonPostorderTraversal");
        buttonPostorderTraversal->setGeometry(QRect(460, 520, 62, 21));
        graphicsViewTree = new QGraphicsView(centralwidget);
        graphicsViewTree->setObjectName("graphicsViewTree");
        graphicsViewTree->setGeometry(QRect(0, 10, 791, 451));
        labelTraversalOutput = new QLabel(centralwidget);
        labelTraversalOutput->setObjectName("labelTraversalOutput");
        labelTraversalOutput->setGeometry(QRect(350, 480, 401, 31));
        labelTraversalOutput->setStyleSheet(QString::fromUtf8("color: rgb(200, 9, 76)"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(280, 490, 71, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ImageLabel->setText(QString());
        buttonBuildTree->setText(QCoreApplication::translate("MainWindow", "Build", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Expression", nullptr));
        comboBoxExpressionType->setItemText(0, QCoreApplication::translate("MainWindow", "Prefix", nullptr));
        comboBoxExpressionType->setItemText(1, QCoreApplication::translate("MainWindow", "Infix", nullptr));
        comboBoxExpressionType->setItemText(2, QCoreApplication::translate("MainWindow", "Postfix", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        buttonInorderTraversal->setText(QCoreApplication::translate("MainWindow", "Infix", nullptr));
        buttonPreorderTraversal->setText(QCoreApplication::translate("MainWindow", "Prefix", nullptr));
        buttonPostorderTraversal->setText(QCoreApplication::translate("MainWindow", "Postfix", nullptr));
        labelTraversalOutput->setText(QCoreApplication::translate("MainWindow", "Loading...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Output:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
