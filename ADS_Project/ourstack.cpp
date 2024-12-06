#include "ourstack.h"
#include <stdexcept>
#include <iostream>
#include "TreeNode.h"

using namespace std;

// Implementations for the OurStack class template

/*template <typename T>
OurStack<T>::OurStack(int size) : capacity(size), top_index(-1) {
    arr = new T[capacity];
}

template <typename T>
OurStack<T>::OurStack(const OurStack& other) : capacity(other.capacity), top_index(other.top_index) {
    arr = new T[capacity];
    for (int i = 0; i <= top_index; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
OurStack<T>& OurStack<T>::operator=(const OurStack& other) {
    if (this != &other) {
        delete[] arr;
        capacity = other.capacity;
        top_index = other.top_index;
        arr = new T[capacity];
        for (int i = 0; i <= top_index; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename T>
OurStack<T>::~OurStack() {
    delete[] arr;
}

template <typename T>
void OurStack<T>::push(const T& element) {
    if (isFull()) {
        throw overflow_error("Stack is full");
    }
    arr[++top_index] = element;
}

template <typename T>
void OurStack<T>::pop() {
    if (isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    --top_index;
}

template <typename T>
T& OurStack<T>::top() {
    if (isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    return arr[top_index];
}

template <typename T>
const T& OurStack<T>::top() const {
    if (isEmpty()) {
        throw underflow_error("Stack is empty");
    }
    return arr[top_index];
}

template <typename T>
bool OurStack<T>::isEmpty() const {
    return top_index == -1;
}

template <typename T>
bool OurStack<T>::isFull() const {
    return top_index == capacity - 1;
}

template <typename T>
int OurStack<T>::size() const {
    return top_index + 1;
}

template <typename T>
void OurStack<T>::clear() {
    top_index = -1;
}

template <typename T>
T& OurStack<T>::at(int index) {
    if (index < 0 || index > top_index) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
const T& OurStack<T>::at(int index) const {
    if (index < 0 || index > top_index) {
        throw out_of_range("Index out of range");
    }
    return arr[index];
}

// Explicit instantiation of OurStack for the types used in the project
template class OurStack<int>;
template class OurStack<double>;
template class OurStack<char>;
template class OurStack<TreeNode*>;
*/
