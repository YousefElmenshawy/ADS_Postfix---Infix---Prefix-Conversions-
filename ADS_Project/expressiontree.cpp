#include "expressiontree.h"
#include <stack>
bool ExpressionTree::isOperator(QChar c){
  return c == '+' || c == '-' || c == '*' || c == '/';
}
void ExpressionTree::inOrderTraversal()
{

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

TreeNode* ExpressionTree::Helper_buildfromPrefix(const QString & prefix) // Ahmed Amgad
{
  int index = 0;
  return buildfromPrefix(prefix, index);
}
TreeNode* ExpressionTree::buildfromPrefix(const QString & prefix, int & index) // Ahmed Amgad
{
    //base case
    if (index >= prefix.length()){
      return nullptr;
    }
    TreeNode* root = new TreeNode(prefix[index]);
    index++;
    if(isOperator(prefix[index])){
      root->left = buildfromPrefix(prefix, index);
      root->right = buildfromPrefix(prefix, index);
      }
    return root;
}
void ExpressionTree::buildfromPostfix(const QString & postfix)
{

}

QString ExpressionTree::ToInfix()
{

}

QString ExpressionTree::ToPostfix()
{

}

QString ExpressionTree::ToPrefix()
{

}
