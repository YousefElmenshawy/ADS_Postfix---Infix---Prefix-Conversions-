ADS: Postfix, Infix, and Prefix Conversions

This project implements algorithms for converting expressions between Postfix, Infix, and Prefix notations. It uses an Expression Tree to facilitate these conversions, leveraging different tree traversals.

Features:

Build an expression tree from any of the three notations (Postfix, Infix, Prefix).

Convert between:

Postfix ↔ Infix

Postfix ↔ Prefix

Infix ↔ Prefix

Evaluate Postfix and Prefix expressions.

Technologies

C++

Qt : For GUI implementation.

How It Works

Expression Tree:

Expressions are parsed and stored as a binary tree.
Operators are stored as internal nodes.
Operands are stored as leaf nodes.
Traversals for Conversion:

Inorder Traversal: Generates Infix expressions.
Preorder Traversal: Generates Prefix expressions.
Postorder Traversal: Generates Postfix expressions.

Validation:

Input expressions are validated to ensure correct format.
Mismatched parentheses or invalid operators are flagged.
