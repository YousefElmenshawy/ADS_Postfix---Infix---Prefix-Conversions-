#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include<QString>

using namespace std;

class ExpressionTree
{
private:

    struct TreeNode {
        QString value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(QString val) : value(val), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;

    void PreOrderTraversal();
    void PostOrderTraversal();//Helper Functions to be included in the Conversions
    bool isOperator(QChar ch);
    int precedence(QChar op);

public:
    ExpressionTree();
    void buildfromPostfix(const QString & postfix); // building expression tree from postfix expression
    TreeNode* buildfromPrefix(const QString & prefix, int & index);
    TreeNode* Helper_buildfromPrefix(const QString & prefix);
    void buildfromInfix(const QString & infix);
    QString ToInfix(TreeNode* Root);
    QString ToPostfix();
    QString ToPrefix();

};

#endif // EXPRESSIONTREE_H
