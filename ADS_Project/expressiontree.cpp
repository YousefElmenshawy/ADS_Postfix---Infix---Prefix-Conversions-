#include "expressiontree.h"

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

void ExpressionTree::buildfromPostfix(const QString &postfix)// Saif Sabry
{

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
