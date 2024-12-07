#ifndef OURSTACK_H
#define OURSTACK_H
#include"TreeNode.h"
#include <stdexcept>

template <typename T>
class OurStack {
public:
    // Constructor
    OurStack(int size = 10); // Default size is 10 if not specified.

    // Copy constructor
    OurStack(const OurStack& other);

    // Assignment operator
    OurStack& operator=(const OurStack& other);

    // Destructor
    ~OurStack();

    void push(const T& element); // Add an element to the top of the stack
    void pop();                  // Remove the top element from the stack
    T& top();                    // Access the top element (modifiable)
    const T& top() const;        // Access the top element (read-only)
    bool empty() const;          // Check if the stack is empty
    int size() const;            // Get the number of elements in the stack


    void clear();                // Remove all elements from the stack
    T& at(int index);            // Access element at a specific index
    const T& at(int index) const; // Access element at a specific index (read-only)

private:
    // Internal helper methods
    bool isFull() const;         // Check if the stack is full (used internally)
    bool isEmpty() const;        // Check if the stack is empty (used internally)

    // Data members
    T* arr;                      // Dynamic array to hold stack elements
    int capacity;                // Maximum capacity of the stack
    int top_index;               // Index of the current top element
};


template <typename T>
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
bool OurStack<T>::empty() const {
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




#endif // OURSTACK_H
