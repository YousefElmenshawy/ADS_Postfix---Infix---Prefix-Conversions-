#include "expressiontree.h"
#include "TreeNode.h"
#include"ourstack.h"
#include <QString>
#include <QVector>
#include<iostream>
#include <QTextStream>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include<QTimer>
#include <QObject>
using namespace std;

ExpressionTree::ExpressionTree(QObject* parent)
    : QObject(parent),           // Initialize base class QObject first
    root(nullptr),              // Initialize root
    // Initialize currentNodeIndex
    timer(new QTimer(this)),currentNodeIndex(0) {   // Initialize timer
    // Connect the timer's timeout signal to moveToNextNode
    connect(timer, &QTimer::timeout, this, &ExpressionTree::moveToNextNode);

}
TreeNode* ExpressionTree::copyTree(TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TreeNode* newNode = new TreeNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
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

    QString postfix = ToPostfix(root);  // Convert the expression tree to postfix notation
    double result = 0;
    OurStack<double> Store(postfix.size());

    // Tokenize the postfix string by splitting it at spaces
    QVector<QString> tokens;
    QString currentToken;

    for (QChar ch : postfix) {
        if (ch == ' ') {
            if (!currentToken.isEmpty()) {
                tokens.append(currentToken);
                currentToken.clear();
            }
        } else {
            currentToken.append(ch);  // Add the character to the current token
        }
    }

    if (!currentToken.isEmpty()) {  // In case there's a last token without a space at the end
        tokens.append(currentToken);
    }

    for (const QString& token : tokens) {
        if (token[0].isDigit()) {
            Store.push(token.toDouble());  // Push the numeric value to the stack
        }
        else if (isOperator(token[0])) {  // Check if the token is an operator
            double a2 = Store.top(); Store.pop();
            double a1 = Store.top(); Store.pop();
            result = applyOperation(a1, a2, token[0]);
            Store.push(result);
        }
    }


    return result;
}

void ExpressionTree::buildfromPostfix(const QString &postfix) // Saif Sabry
{
    // If the postfix string is empty, set the root to nullptr and return immediately.
    if (postfix.isEmpty()) {
        root = nullptr;
        return;
    }
    // Create a stack to store TreeNode pointers during tree construction, with a size based on the length of the postfix expression.
    OurStack<TreeNode*> s(postfix.size());
    QString multi_digit;
    // Iterate through each character in the postfix expression.
    for (QChar ch : postfix) {
        // If the character is a digit, append it to the multi-digit string.
        if (ch.isDigit()) {
            multi_digit.append(ch);
        }
        else {
            // If a multi-digit operand has been collected, create a new TreeNode for it, push it onto the stack, and clear the multi-digit string.
            if (!multi_digit.isEmpty()) {
                s.push(new TreeNode(multi_digit));
                multi_digit.clear();
            }
            // If the character is an operator, check that there are at least two operands on the stack.
            if (isOperator(ch)) {
                if (s.size() < 2) {
                    throw std::invalid_argument("Invalid postfix expression: not enough operands for operator!");
                }
                // Pop the top two nodes from the stack to use as children for the new operator node.
                TreeNode* rightChild = s.top();
                s.pop();
                TreeNode* leftChild = s.top();
                s.pop();
                // Create a new TreeNode for the operator and attach the left and right children.
                TreeNode* newNode = new TreeNode(ch);
                newNode->left = leftChild;
                newNode->right = rightChild;
                 // Push the new operator node back onto the stack.
                s.push(newNode);
            }
            else if (!ch.isSpace()) {
                throw std::invalid_argument("Invalid character in postfix expression!");
            }
        }
    }
     // If there's any remaining multi-digit operand, create a TreeNode for it and push it onto the stack.
    if (!multi_digit.isEmpty()) {
        s.push(new TreeNode(multi_digit));
    }
    //case handling for too many operands
    if (s.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression: too many operands!");
    }
    // Set the root of the tree to the single remaining node on the stack.
    root = s.top();
    s.pop();
}
void ExpressionTree::buildfromPrefix(const QString & prefix) // Ahmed Amgad
{   //if the expression is empty an error is thrown
    if (prefix.isEmpty()) {
        throw std::invalid_argument("Prefix expression is empty!");
    }

    OurStack<TreeNode*> s(prefix.size());//a stack to hold the operators and operands as treeNodes
    QVector<QString> tokens;//a vector to split the tokens in to traverse

    QString currentToken;
    for (QChar ch : prefix) {//traverses the expression and every string or char seperated by spaces into a tokens vector
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
    //traverses the tokens in reverse except for the first token
    for (int i = tokens.size() - 1; i >= 0; --i) {
        QString token = tokens[i];
        //if at any point an operator is encountered and there are no operands from the stack to be popped to
        //be assigned as left and right childs of the operator then the expression must be invalid
        if (isOperator(token)) {
            if (s.size() < 2) {//be assigned as left and right child of the oper
                throw std::invalid_argument("Invalid prefix expression: not enough operands for operator!");
            }
            //once the operator is encountered a new TreeNode is made andd two operands are popped from the stack to be its left and right child
            TreeNode* node = new TreeNode(token);
            node->left = s.top(); s.pop();
            node->right = s.top(); s.pop();
            // The operator is then pushed into the TreeNode Stack and it will get poped along with its sibling to be children of a parent operator
            s.push(node);
        } else {
            //if it is an operand simply push it in the stack
            s.push(new TreeNode(token));
        }
    }
    //At the end there must be one remaing item which will be the root
    if (s.size() != 1) {
        throw std::invalid_argument("Invalid prefix expression: too many operands!");
    }
    //the reamaining item is the root
    root = s.top();
}

void ExpressionTree::buildfromInfix(QString &infix) {// Yousef Elmenshawy

    // Yousef Elmenshawy
    if (infix.isEmpty()) {
        throw std::invalid_argument("Error: Infix expression is empty!");
    }

    // Remove spaces
    infix=removeSpaces(infix);
    OurStack<TreeNode*> nodeStack(infix.size());       // Stack for operands/subtrees
    OurStack<QChar> operatorStack(infix.size());       // Stack for operators

    // Process the infix expression character by character
    int i = 0;
    while (i < infix.size()) {
        if (infix[i].isSpace()) {
            i++; // Skip whitespaces
            continue;
        }

        if (infix[i].isDigit() || infix[i].isLetter()) { // Handling multi-digit or variable names
            QString numStr;
            while (i < infix.size() && (infix[i].isDigit() || infix[i].isLetter())) {
                numStr += infix[i++];
            }
            nodeStack.push(new TreeNode(numStr)); // Push operand as a tree node
        } else if (infix[i] == '(') {
            operatorStack.push(infix[i]);
            i++;
        } else if (infix[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.pop(); // Remove the '('
            i++;
        } else if (infix[i] == '-' &&
                   (i == 0 || infix[i - 1] == '(' || isOperator(infix[i - 1].toLatin1()))) {
            // Unary minus case: Start a negative number
            i++; // Skip the '-'
            QString numStr = "-";
            while (i < infix.size() && infix[i].isDigit()) {
                numStr += infix[i++];
            }
            nodeStack.push(new TreeNode(numStr)); // Push negative operand as a tree node
        } else if (isOperator(infix[i].toLatin1())) {
            while (!operatorStack.empty() &&
                   precedence(operatorStack.top().toLatin1()) >= precedence(infix[i].toLatin1())) {
                processOperator(nodeStack, operatorStack);
            }
            operatorStack.push(infix[i]); // Push the current operator
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
        cerr << "Error: Failed to build expression tree!";
    }
}


QString ExpressionTree::removeSpaces(const QString& str) {//Yousef Elmenshawy
    QString result;
    for (QChar ch : str) {
        if (!ch.isSpace()) {
            result += ch;
        }
    }
    return result;
}

QString ExpressionTree::ToInfix(TreeNode *Root)// Yousef Elmenshawy
{

    QString InfixExp = "";
    if (Root == nullptr) {
        return InfixExp;  // Base case: If the node is null, return
    }

    InfixExp+= ToInfix(Root->left); //Traverse left

    InfixExp+= Root->value; // visit the node
    InfixExp+=" ";
    InfixExp+= ToInfix(Root->right); //Traverse right


    return InfixExp;

}

void ExpressionTree::processOperator(OurStack<TreeNode*>& nodeStack, OurStack<QChar>& operatorStack) {// Helper function to avoid reptetion in Build from Infix code
    if (nodeStack.size() < 2) {
        cerr << "Error: Insufficient operands for operator!" << endl;// Yousef Elmenshawy
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

TreeNode *ExpressionTree::Root_Accesser()// Yousef Elmenshawy
{
    return root;
}

void ExpressionTree::visualizeTree(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset) {
    if (!node) return;

    // Draw current node
    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 30, y - 30, 60, 60, QPen(Qt::black), QBrush(Qt::lightGray));
    QGraphicsTextItem* text = scene->addText(QString(node->value));
    text->setDefaultTextColor(Qt::black);
    text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

    // Make the text a child of the ellipse
    text->setParentItem(ellipse);

    nodeEllipseList.append({node, ellipse});
    // Recursively draw left and right subtrees with calculated offsets
    if (node->left) {
        scene->addLine(x, y + 30, x - hOffset, y + vOffset - 30, QPen(Qt::black)); // Line to left child
        visualizeTree(scene, node->left, x - hOffset, y + vOffset, hOffset / 2, vOffset);
    }

    if (node->right) {
        scene->addLine(x, y + 30, x + hOffset, y + vOffset - 30, QPen(Qt::black)); // Line to right child
        visualizeTree(scene, node->right, x + hOffset, y + vOffset, hOffset / 2, vOffset);
    }
}
void ExpressionTree::animateTraversal(QGraphicsScene* scene, TreeNode* root, const QString& order, QString& traversalString) {
    currentNodeIndex = 0;
    nodesToColor.clear();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ExpressionTree::moveToNextNode);
    // Clear the list of ellipses before traversal
    for (auto& pair : nodeEllipseList) {
        pair.ellipse->setBrush(QBrush(Qt::lightGray));  // Reset to light gray color
    }
    if (order == "inorder") {
        traverseInorder(scene, root, 400, 100, 100, 100, traversalString); // Initial position and offset
    } else if (order == "preorder") {
        traversePreorder(scene, root, 400, 100, 100, 100,traversalString);
    } else if (order == "postorder") {
        traversePostorder(scene, root, 400, 100, 100, 100,traversalString);
    }

    timer->start(1000);  // Set the interval for each node color change

}

void ExpressionTree::traverseInorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset,QString& traversalString) {
    if (!node) return;

    // Traverse the left subtree
    traverseInorder(scene, node->left, x - hOffset, y + vOffset, hOffset / 2, vOffset, traversalString);

    // Process current node
    for (int i = 0; i < nodeEllipseList.size(); ++i) {
        if (nodeEllipseList[i].node == node) {
            nodesToColor.append(nodeEllipseList[i].ellipse);
            break;
        }
    }
    traversalString += node->value + " ";  // Add current node's value to the traversal string
    emit updateTraversalOutput(traversalString);  // Emit signal to update label with the accumulated string

    // Traverse the right subtree
    traverseInorder(scene, node->right, x + hOffset, y + vOffset, hOffset / 2, vOffset,  traversalString);
}

void ExpressionTree::traversePreorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset,QString& traversalString) {
    if (!node) return;

    // Process current node
    for (int i = 0; i < nodeEllipseList.size(); ++i) {
        if (nodeEllipseList[i].node == node) {
            nodesToColor.append(nodeEllipseList[i].ellipse);
            break;
        }
    }
    traversalString += node->value + " ";  // Add current node's value to the traversal string
    emit updateTraversalOutput(traversalString);  // Emit signal to update label with the accumulated string

    // Traverse the left subtree
    traversePreorder(scene, node->left, x - hOffset, y + vOffset, hOffset / 2, vOffset,traversalString);

    // Traverse the right subtree
    traversePreorder(scene, node->right, x + hOffset, y + vOffset, hOffset / 2, vOffset, traversalString);
}

void ExpressionTree::traversePostorder(QGraphicsScene* scene, TreeNode* node, double x, double y, double hOffset, double vOffset, QString& traversalString) {
    if (!node) return;

    // Traverse the left subtree
    traversePostorder(scene, node->left, x - hOffset, y + vOffset, hOffset / 2, vOffset,  traversalString);

    // Traverse the right subtree
    traversePostorder(scene, node->right, x + hOffset, y + vOffset, hOffset / 2, vOffset, traversalString);

    // Process current node

    for (int i = 0; i < nodeEllipseList.size(); ++i) {
        if (nodeEllipseList[i].node == node) {
            nodesToColor.append(nodeEllipseList[i].ellipse);
            break;
        }
    }
    traversalString += node->value + " ";  // Add current node's value to the traversal string
    emit updateTraversalOutput(traversalString);  // Emit signal to update label with the accumulated string

    // Traverse the right subtree
}

void ExpressionTree::colorNode(QGraphicsEllipseItem* ellipse, QColor color) {
    ellipse->setBrush(QBrush(color));
}

void ExpressionTree::moveToNextNode() {
    if (currentNodeIndex < nodesToColor.size()) {
        // Color the next node (current node index)
        colorNode(nodesToColor[currentNodeIndex], Qt::yellow);

        // Move to the next node
        ++currentNodeIndex;
    } else {
        // Stop the timer when all nodes are processed
        timer->stop();
    }
}
