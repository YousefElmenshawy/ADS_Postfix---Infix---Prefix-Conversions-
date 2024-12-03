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

void ExpressionTree::buildfromInfix(QString &infix) {// Yousef Elmenshawy

        // Yousef Elmenshawy
        if (infix.isEmpty()) {
            throw std::invalid_argument("Error: Infix expression is empty!");
        }

        // Remove spaces
        infix=removeSpaces(infix);
        stack<TreeNode*> nodeStack;       // Stack for operands/subtrees
        stack<QChar> operatorStack;       // Stack for operators

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


    QString ExpressionTree::removeSpaces(const QString& str) {
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
void ExpressionTree::displayConversionMenu(ExpressionTree& tree) {
    QString input;
    string Input;
    int choice=0;
    cout << "Welcome to our Tree of expressions!";
    while (choice!=7) {
        cout << "\nExpression Conversion Menu:\n";
        cout << "1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Postfix to Infix\n";
        cout << "4. Postfix to Prefix\n";
        cout << "5. Prefix to Infix\n";
        cout << "6. Prefix to Postfix\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cout << "Enter the expression: ";
        cin.ignore(); // Clear newline from the input buffer
        cin>>Input;
        input = QString::fromStdString(Input);

        try {
            switch (choice) {
            case 1: // Infix to Postfix
                tree.buildfromInfix(input);
                cout << "Postfix Expression: " << tree.ToPostfix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 2: // Infix to Prefix
                tree.buildfromInfix(input);
                cout << "Prefix Expression: " << tree.ToPrefix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 3: // Postfix to Infix
                tree.buildfromPostfix(input);
                cout << "Infix Expression: " << tree.ToInfix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 4: // Postfix to Prefix
                tree.buildfromPostfix(input);
                cout << "Prefix Expression: " << tree.ToPrefix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 5: // Prefix to Infix
                tree.buildfromPrefix(input);
                cout << "Infix Expression: " << tree.ToInfix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 6: // Prefix to Postfix
                tree.buildfromPrefix(input);
                cout << "Postfix Expression: " << tree.ToPostfix(tree.Root_Accesser()).toStdString() << "\n";
                break;
            case 7:
                cout << "Exiting the menu. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
            }
        } catch (const std::exception& e) {
            cout << e.what() << "\n";// just in case if there were any errors inside the switch case but it should be fine
        }
    }
}
