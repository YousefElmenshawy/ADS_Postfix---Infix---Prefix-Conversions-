#ifndef TREENODE_H
#define TREENODE_H
#include <QString>
using namespace std;

class TreeNode {
public:
    QString value;
    TreeNode* left;
    TreeNode* right;

    // Constructor for TreeNode
    TreeNode(QString val) : value(val), left(nullptr), right(nullptr) {}
    TreeNode() : value(""), left(nullptr), right(nullptr) {}
};
#endif //TREENODE_H
