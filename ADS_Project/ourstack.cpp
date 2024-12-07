#include "ourstack.h"
#include <stdexcept>
#include <iostream>
#include "TreeNode.h"

using namespace std;

//No Implementations for the OurStack class template in the .cpp file because of the error caused by the template.
//QT struggles to find refrence for the implementations when they are not in the .h file.


// Explicit instantiation of OurStack for the types used in the project
template class OurStack<int>;
template class OurStack<double>;
template class OurStack<char>;
template class OurStack<TreeNode*>;

