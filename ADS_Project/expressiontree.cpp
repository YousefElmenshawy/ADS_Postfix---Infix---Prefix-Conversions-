#include "expressiontree.h"
#include <stack>
#include <QString>
#include <QVector>
#include<iostream>
#include <QTextStream>
using namespace std;
ExpressionTree::ExpressionTree():root(nullptr) {

}
ExpressionTree::ExpressionTree(const ExpressionTree& other) : root(nullptr) {
    if (other.root != nullptr) {
        root = copyTree(other.root);
    }
}
ExpressionTree::TreeNode* ExpressionTree::copyTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}
ExpressionTree& ExpressionTree::operator=(const ExpressionTree& other) {
    if (this == &other) {
        return *this;
    }
    reset();
    if (other.root != nullptr) {
        root = copyTree(other.root);
    }
    return *this;
}
void ExpressionTree::clearTree(TreeNode *node) {
    if (node == nullptr) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void ExpressionTree::reset() {
    clearTree(root);
    root = nullptr;
}

ExpressionTree::~ExpressionTree() {
    clearTree(root);
}
bool ExpressionTree::isOperator(QChar c){
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}
bool ExpressionTree::isOperator(QString s){
    return s == "+" || s == "-" || s == "*" || s == "/" || s =="%";
}
int ExpressionTree::precedence(QChar op) { // Helper Function for Build from Infix.(Yousef Elmenshawy)

    if(op=='+'||op=='-') {
        return 1;
    }
    else if(op=='*'||op=='/'||op=='%') {
        return 2;
    }
    else
        return 0;
    // Precedence rules:
    // - Return 1 for + and -
    // - Return 2 for *, /, and %
    // - Return 0 for any other character (default case)
}

double ExpressionTree::applyOperation(double a, double b, QChar op) {
    double result = 0;
    int A=static_cast<int>(a); int B=static_cast<int>(b);
    if (op == '+') {
        result = a + b;
    } else if (op == '-') {
        result = a - b;
    } else if (op == '*') {
        result = a * b;
    } else if (op == '/') {
        if (b == 0) {
            throw runtime_error("Error: Division by zero");
        } else {
            result = a / b;
        }
    } else if (op == '%') {
        result = A % B;
    }else {
        throw runtime_error("Error: Invalid Operation");
    }
    return result;

}

double ExpressionTree::evaluateExpression()
{
    QString postfix = ToPostfix(root);
    double result = 0;
    stack<double> Store;
    QTextStream ss(&postfix);
    QString token;
    while (!ss.atEnd()) {
        ss >> token;
        if(token[0].isDigit()) {
            Store.push(token.toDouble());
        }
        else if(isOperator(token[0])) {

            double a2 = Store.top(); Store.pop();
            double a1=Store.top(); Store.pop();
            result= applyOperation(a1,a2,token[0]);
            Store.push(result);
        }

    }

    return result;
}

void ExpressionTree::buildfromPostfix(const QString &postfix) // Saif Sabry
{
    if (postfix.isEmpty()) {
        root = nullptr;
        return;
    }

    stack<TreeNode*> s;
    QString multi_digit;
    for (QChar ch : postfix) {
  if (ch.isDigit()) {
      multi_digit.append(ch);
  }
  else {
      if (!multi_digit.isEmpty()) {
          s.push(new TreeNode(multi_digit));
          multi_digit.clear();
      }

      if (isOperator(ch)) {
          if (s.size() < 2) {
              throw std::invalid_argument("Invalid postfix expression: not enough operands for operator!");
          }
          TreeNode* rightChild = s.top();
          s.pop();
          TreeNode* leftChild = s.top();
          s.pop();

          TreeNode* newNode = new TreeNode(ch);
          newNode->left = leftChild;
          newNode->right = rightChild;
          s.push(newNode);
      }
      else if (!ch.isSpace()) {
          throw std::invalid_argument("Invalid character in postfix expression!");
      }
  }
    }
    if (!multi_digit.isEmpty()) {
        s.push(new TreeNode(multi_digit));
    }
    if (s.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression: too many operands!");
    }
    root = s.top();
    s.pop();
}
void ExpressionTree::buildfromPrefix(const QString & prefix) // Ahmed Amgad
{
    if (prefix.isEmpty()) {
        throw std::invalid_argument("Prefix expression is empty!");
    }

    stack<TreeNode*> s;
    QVector<QString> tokens;

    QString currentToken;
    for (QChar ch : prefix) {
        if (ch == ' ') {
            if (!currentToken.isEmpty()) {
                tokens.append(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken.append(ch);
        }
    }

    // Add the last token if any
    if (!currentToken.isEmpty()) {
        tokens.append(currentToken);  // Add the final token to the QVector
    }

    for (int i = tokens.size() - 1; i >= 0; --i) {
        QString token = tokens[i];

        if (isOperator(token)) {
            if (s.size() < 2) {
                throw std::invalid_argument("Invalid prefix expression: not enough operands for operator!");
            }

            TreeNode* node = new TreeNode(token);
            node->left = s.top(); s.pop();
            node->right = s.top(); s.pop();
            s.push(node);
        } else {
            s.push(new TreeNode(token));
        }
    }

    if (s.size() != 1) {
        throw std::invalid_argument("Invalid prefix expression: too many operands!");
    }

    root = s.top();
}

void ExpressionTree::buildfromInfix(const QString &infix) {// Yousef Elmenshawy
    if (infix.isEmpty()) {
        cerr << "Error: Infix expression is empty!" << endl;
        return;
    }

    stack<TreeNode*> nodeStack;       // Stack for operands/subtrees
    stack<QChar> operatorStack;        // Stack for operators

    // Process the infix expression character by character
    int i = 0;
    while (i < infix.size()) {
        if (infix[i].isSpace()) {
            i++; // Skip whitespaces
            continue;
        }

        if (infix[i].isDigit()) {// Handling Multidigit
            QString numStr;
            while (i < infix.size() && infix[i].isDigit()) {
                numStr += infix[i++];
            }
            nodeStack.push(new TreeNode(numStr));  // Push operand as a tree node
        }
        else if (infix[i] == '(') {
            operatorStack.push(infix[i]);
            i++;
        }
        else if (infix[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.pop();  // Remove the '('
            i++;
        }
        else if (isOperator(infix[i])) {
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(infix[i])) {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.push(infix[i]);  // Push the current operator
            i++;
        }
    }

    // Process remaining operators
    while (!operatorStack.empty()) {
        processOperator(nodeStack, operatorStack);
    }

    // The root of the tree is the only node left in the stack
    if (!nodeStack.empty()) {
        root = nodeStack.top();
        nodeStack.pop();
    } else {
        cerr << "Error: Failed to build expression tree!" << endl;
    }
}


QString ExpressionTree::ToInfix(TreeNode *Root)
{
    QString InfixExp = "";
    if (Root == nullptr) {
        return InfixExp;  // Base case: If the node is null, return
    }

    InfixExp+= ToPostfix(Root->left); //Traverse left

    InfixExp+= Root->value; // visit the node
    InfixExp+=" ";
    InfixExp+=ToPostfix(Root->right); //Traverse right


    return InfixExp;

}

void ExpressionTree::processOperator(stack<TreeNode*>& nodeStack, stack<QChar>& operatorStack) {// Helper function to avoid reptetion in Build from Infix code
    if (nodeStack.size() < 2) {
        cerr << "Error: Insufficient operands for operator!" << endl;
        return;
    }

    // Pop operator
    QChar op = operatorStack.top();
    operatorStack.pop();

    // Pop operands
    TreeNode* right = nodeStack.top(); nodeStack.pop();
    TreeNode* left = nodeStack.top(); nodeStack.pop();

    // Create operator node
    TreeNode* opNode = new TreeNode(QString(op));
    opNode->left = left;
    opNode->right = right;

    // Push the new subtree
    nodeStack.push(opNode);
}

QString ExpressionTree::ToPostfix(TreeNode* Root) //Koussay Jaballah
{
    QString PostfixExp = "";
    if (Root == nullptr) {
        return PostfixExp;  // Base case: If the node is null, return
    }

    PostfixExp+= ToPostfix(Root->left); //Traverse left
     PostfixExp+=ToPostfix(Root->right); //Traverse right

    PostfixExp+= Root->value; // visit the node
    PostfixExp+=" ";
    return PostfixExp;
}

QString ExpressionTree::ToPrefix(TreeNode* Root) //Koussay Jaballah
{
    QString PrefixExp = "";
    if (Root == nullptr) {
        return PrefixExp;  // Base case: If the node is null, return
    }
    PrefixExp+= Root->value; // visit the node
    PrefixExp+=" ";

    PrefixExp= PrefixExp+ ToPrefix(Root->left); //Traverse left
   PrefixExp+= ToPrefix(Root->right); //Traverse right

    return PrefixExp;
}

ExpressionTree::TreeNode *ExpressionTree::Root_Accesser()
{
    return root;
}
