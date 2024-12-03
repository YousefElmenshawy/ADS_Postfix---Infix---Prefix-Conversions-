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
    bool isOperator(QString s);
    double applyOperation(double a, double b, QChar op);
    int precedence(QChar op);
    void processOperator(stack<TreeNode*>& nodeStack, stack<QChar>& operatorStack);
    TreeNode* copyTree(TreeNode* node);

public:
    ExpressionTree();
    void clearTree(TreeNode* node);
    ExpressionTree(const ExpressionTree& other);
    ExpressionTree& operator=(const ExpressionTree& other);
    void reset();
    void displayConversionMenu(ExpressionTree& tree);
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


};

#endif // EXPRESSIONTREE_H
