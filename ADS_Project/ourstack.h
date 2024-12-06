#ifndef OURSTACK_H
#define OURSTACK_H

#include <stdexcept>

template <typename T>
class OurStack {
public:
    // Constructor
    explicit OurStack(int size = 10); // Default size is 10 if not specified.

    // Copy constructor
    OurStack(const OurStack& other);

    // Assignment operator
    OurStack& operator=(const OurStack& other);

    // Destructor
    ~OurStack();

    // STL and Qt-style methods
    void push(const T& element); // Add an element to the top of the stack
    void pop();                  // Remove the top element from the stack
    T& top();                    // Access the top element (modifiable)
    const T& top() const;        // Access the top element (read-only)
    bool empty() const;          // Check if the stack is empty
    int size() const;            // Get the number of elements in the stack

    // Qt-style methods
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

#endif // OURSTACK_H
