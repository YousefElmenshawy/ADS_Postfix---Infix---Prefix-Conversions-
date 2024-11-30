#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include<QString>
#include<stack>

using namespace std;

class ExpressionTree
{
private:

    struct TreeNode {
        QString value;
        TreeNode* left;
        TreeNode* right;
        TreeNode( QString val) : value(val), left(nullptr), right(nullptr) {}
    };
    TreeNode* root;

    //Helper Functions to be included in the Conversions
    bool isOperator(QChar ch);
    bool isStringOperator(QString c);
    int precedence(QChar op);
    void processOperator(stack<TreeNode*>& nodeStack, stack<QChar>& operatorStack);

public:
    ExpressionTree();
    void clearTree(TreeNode* node);

    void reset();

    ~ExpressionTree();
    void buildfromPostfix(const QString & postfix); // building expression tree from postfix expression
    void buildfromPrefix(const QString & prefix);
    void buildfromInfix(const QString & infix);
    QString ToInfix(TreeNode* Root);
    QString ToPostfix(TreeNode* Root);
    QString ToPrefix(TreeNode* Root);
    TreeNode * Root_Accesser ();// helper function for the main


};

#endif // EXPRESSIONTREE_H
