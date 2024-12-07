#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include<QString>
#include<ourstack.h>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>


using namespace std;

class ExpressionTree : public QObject
{
     Q_OBJECT
private:


    TreeNode* root;

    //Helper Functions to be included in the Conversions
    bool isOperator(QChar ch);
    bool isOperator(QString s);
    double applyOperation(double a, double b, QChar op);
    int precedence(QChar op);
    void processOperator(OurStack<TreeNode*>& nodeStack, OurStack<QChar>& operatorStack);
    TreeNode* copyTree(TreeNode* node);


public:
    ExpressionTree(QObject* parent = nullptr);
    void clearTree(TreeNode* node);
    void reset();
    ~ExpressionTree();
    double evaluateExpression();
    void buildfromPostfix(const QString & postfix); // building expression tree from postfix expression
    void buildfromPrefix(const QString & prefix);
    void buildfromInfix(QString & infix);
    QString removeSpaces(const QString& str);
    QString ToInfix(TreeNode* Root);
    QString ToPostfix(TreeNode* Root);
    QString ToPrefix(TreeNode* Root);
    TreeNode * Root_Accesser ();// helper function for the main
    void visualizeTree(QGraphicsScene* scene, TreeNode* root, double x, double y, double hOffset, double vOffset);
    void traverseInorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset, QString&traversalString);
    void traversePreorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset, QString&traversalString);
    void traversePostorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset, QString&traversalString);
    void animateTraversal(QGraphicsScene* scene, TreeNode* root, const QString& order,  QString&traversalString);
    void colorNode(QGraphicsEllipseItem* ellipse, QColor color);
    void moveToNextNode();
    struct NodeEllipsePair {
        TreeNode* node;
        QGraphicsEllipseItem* ellipse;
    };

    QList<NodeEllipsePair> nodeEllipseList;
    QTimer* timer;
    QList<QGraphicsEllipseItem*> nodesToColor;
    int currentNodeIndex;
signals:
    void updateTraversalOutput( const QString  &traversalString);

};

#endif // EXPRESSIONTREE_H
