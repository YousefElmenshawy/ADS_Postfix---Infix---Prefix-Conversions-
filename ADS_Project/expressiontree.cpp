#include "expressiontree.h"
#include <stack>
#include <QString>
#include <QVector>
bool ExpressionTree::isOperator(QChar c){
  return c == '+' || c == '-' || c == '*' || c == '/';
}
bool ExpressionTree::isStringOperator(QString c){
    return c == "+" || c == "-" || c == "*" || c == "/";
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


void ExpressionTree::PreOrderTraversal()
{

}

void ExpressionTree::PostOrderTraversal()
{

}

ExpressionTree::ExpressionTree():root(nullptr) {






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

        if (isStringOperator(token)) {
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

void ExpressionTree::buildfromInfix(const QString &infix)// Yousef Elmenshawy
{

    stack<TreeNode*> nodeStack;  // Stack to hold TreeNode pointers (operands and subtrees)
    stack<QChar> operatorStack;  // Stack to hold operators

    int i = 0;  // Index to traverse the string
    while (i < infix.size()) {
        // Skip spaces
        if (infix[i].isSpace()) {
            i++;
            continue;
        }

        // Handle multi-digit numbers
        if (infix[i].isDigit()) {
            QString numStr;
            while (i < infix.size() && infix[i].isDigit()) {
                numStr += infix[i];
                i++;
            }
            // Create a new TreeNode for the number and push it to the node stack
            TreeNode* numNode = new TreeNode(numStr);
            nodeStack.push(numNode);
            continue;  // Skip incrementing `i` as it's already done in the loop
        }

        // Handle opening parenthesis
        else if (infix[i] == '(') {
            operatorStack.push(infix[i]);
        }

        // Handle closing parenthesis
        else if (infix[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                // Pop operator and create subtree
                QChar op = operatorStack.top();
                operatorStack.pop();

                // Pop two nodes from the node stack
                TreeNode* right = nodeStack.top();
                nodeStack.pop();
                TreeNode* left = nodeStack.top();
                nodeStack.pop();

                // Create a new operator node and attach left and right as children
                TreeNode* opNode = new TreeNode(op);
                opNode->left = left;
                opNode->right = right;

                // Push the new subtree back onto the node stack
                nodeStack.push(opNode);
            }
            operatorStack.pop();  // Remove the '('
        }

        // Handle operators
        else if (isOperator(infix[i])) {
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top()) >= precedence(infix[i])) {
                // Pop operator and create subtree
                QChar op = operatorStack.top();
                operatorStack.pop();

                // Pop two nodes from the node stack
                TreeNode* right = nodeStack.top();
                nodeStack.pop();
                TreeNode* left = nodeStack.top();
                nodeStack.pop();

                // Create a new operator node and attach left and right as children
                TreeNode* opNode = new TreeNode(op);
                opNode->left = left;
                opNode->right = right;

                // Push the new subtree back onto the node stack
                nodeStack.push(opNode);
            }
            operatorStack.push(infix[i]);  // Push current operator onto the stack
        }

        i++;  // Move to the next character
    }

    // Process remaining operators in the operator stack
    while (!operatorStack.empty()) {
        QChar op = operatorStack.top();
        operatorStack.pop();

        // Pop two nodes from the node stack
        TreeNode* right = nodeStack.top();
        nodeStack.pop();
        TreeNode* left = nodeStack.top();
        nodeStack.pop();

        // Create a new operator node and attach left and right as children
        TreeNode* opNode = new TreeNode(op);
        opNode->left = left;
        opNode->right = right;

        // Push the new subtree back onto the node stack
        nodeStack.push(opNode);
    }

    // The root of the tree will be the only element left in the node stack
    root = nodeStack.top();
    nodeStack.pop();

}



QString ExpressionTree::ToInfix(TreeNode* Root)// Yousef Elmenshawy
{
    QString InfixExp="";
    if (Root == nullptr) {
        return InfixExp;  // Base case: If the node is null, return
    }

    // Traverse the left subtree
    ToInfix(Root->left);

    // Visit the current node
    InfixExp+= Root->value;
    InfixExp+=" ";

    // Traverse the right subtree
   ToInfix(Root->right);
}

QString ExpressionTree::ToPostfix(TreeNode* Root) //Koussay Jaballah
{
    QString PostfixExp = "";
    if (Root == nullptr) {
        return PostfixExp;  // Base case: If the node is null, return
    }

    ToPostfix(Root->left); //Traverse left
    ToPostfix(Root->right); //Traverse right

    PostfixExp+= Root->value; // visit the node
    PostfixExp+=" ";
}

QString ExpressionTree::ToPrefix(TreeNode* Root) //Koussay Jaballah
{
    QString PrefixExp = "";
    if (Root == nullptr) {
        return PrefixExp;  // Base case: If the node is null, return
    }
    PrefixExp+= Root->value; // visit the node
    PrefixExp+=" ";

    ToPrefix(Root->left); //Traverse left
    ToPrefix(Root->right); //Traverse right


}
